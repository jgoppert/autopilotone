#ifndef AUTOPILOTONE_OS_LINUX_HPP_
#define AUTOPILOTONE_OS_LINUX_HPP_

#include <iostream>
#include <stdexcept>
#include "../interfaces.hpp"
#include <simgear/timing/timestamp.hxx>
#include <simgear/threads/SGThread.hxx>
#include <simgear/threads/SGGuard.hxx>
#include <simgear/threads/SGQueue.hxx>
#include <simgear/io/sg_socket.hxx>

namespace autopilotone {

class Mutex: public MutexInterface {
public:
	void lock() {
		return m_mutex.lock();
	}
	void unlock() {
		return m_mutex.unlock();
	}
	virtual ~Mutex() {
	}
	;
private:
	SGMutex m_mutex;
};

class Debug: public DebugInterface {
public:
	void send(const std::string & str) {
		ScopedLock lock(m_mutex);
		std::cout << str << std::endl;
	}
	virtual ~Debug() {
	}
	;
private:
	Mutex m_mutex;
};

class Clock: public ClockInterface {
public:
	Clock() :
			m_clock(SGTimeStamp::now()) {
	}
	void sleepMicros(uint64_t micros) {
		SGTimeStamp::sleepFor(SGTimeStamp::fromUSec(micros));
	}
	uint64_t get_micros() {
		return (SGTimeStamp::now() - m_clock).toUSecs();
	}
	virtual ~Clock() {
	}
	;
private:
	SGTimeStamp m_clock;
} clock;

class Thread: public SGThread {
};

class Serial: public SerialInterface {
public:
	Serial() :
			m_channelSend(new SGSocket("127.0.0.1", "5001", "udp")),
			m_channelReceive(new SGSocket("", "5002", "udp")),
			m_mutexSend(), m_mutexReceive(),
			m_readBuffer() {
		if (!m_channelSend->open(SG_IO_OUT)) {
			throw std::runtime_error("failed to connect send channel");
		}
		if (!m_channelReceive->open(SG_IO_IN)) {
			throw std::runtime_error("failed to connect receive channel");
		}
	}
	virtual ~Serial() {
		ScopedLock lockReceive(m_mutexReceive);
		ScopedLock lockSend(m_mutexSend);
		m_channelSend->close();
		m_channelReceive->close();
	}
	bool available() {
		ScopedLock lock(m_mutexReceive);
		return (m_readBuffer.size());
	}
	uint8_t read() {
		ScopedLock lock(m_mutexReceive);
		if (m_readBuffer.size() < 1) {
			return (0);
		} else {
			return (m_readBuffer.pop());
		}
	}
	void write(const uint8_t * c, size_t bytes) {
		ScopedLock lock(m_mutexSend);
		m_channelSend->write((const char *) c, bytes);
	}
	void update() {
		ScopedLock lock(m_mutexReceive);
		char buffer[100];
		int bytesRead = m_channelReceive->read(buffer, 100);
		//std::cout << "bytesRead : " << bytesRead << std::endl;
		if (bytesRead > 0) {
			for (int i = 0; i < bytesRead; i++) {
				m_readBuffer.push(buffer[i]);
				//std::cout << "pushing back: " << buffer[i] << std::endl;
			}
		}
	}
private:
	SGIOChannel * m_channelSend;
	SGIOChannel * m_channelReceive;
	Mutex m_mutexSend;
	Mutex m_mutexReceive;
	SGBlockingQueue<uint8_t> m_readBuffer;
};

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_LINUX_HPP_
