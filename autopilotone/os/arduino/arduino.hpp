#ifndef AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
#define AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_

#include "../../interfaces.hpp"

namespace autopilotone {

// no need for mutex on arduino, single threaded
class Mutex: public MutexInterface {
public:
	void lock() {
	}
	void unlock() {
	}
};

class Debug: public DebugInterface {
public:
	void write(const char * buf, uint32_t bytes) {
		ScopedLock lock(m_mutex);
        for (int i=0;i<bytes;i++) {
            Serial.print(buf[i]);
        }
	}
private:
	Mutex m_mutex;
};

class Clock: public ClockInterface {
public:
	Clock() {
	}
	void sleepMicros(uint64_t micros) {
        // TODO need to implement task scheduling
        //delayMicros(micros);
	}
	uint64_t get_micros() {
        return micros();
	}
};

//class Thread: public SGThread {
//};

//class Serial: public SerialInterface {
//public:
	//Serial() {
	//}
	//virtual ~Serial() {
		//ScopedLock lockReceive(m_mutexReceive);
		//ScopedLock lockSend(m_mutexSend);
		//m_channelSend->close();
		//m_channelReceive->close();
	//}
	//bool available() {
		//ScopedLock lock(m_mutexReceive);
		//return (m_readBuffer.size());
	//}
	//uint8_t read() {
		//ScopedLock lock(m_mutexReceive);
		//if (m_readBuffer.size() < 1) {
			//return (0);
		//} else {
			//return (m_readBuffer.pop());
		//}
	//}
	//void write(const uint8_t * c, uint32_t bytes) {
		//ScopedLock lock(m_mutexSend);
		//m_channelSend->write((const char *) c, bytes);
	//}
	//void update() {
		//ScopedLock lock(m_mutexReceive);
		//char buffer[100];
		//int bytesRead = m_channelReceive->read(buffer, 100);
		////std::cout << "bytesRead : " << bytesRead << std::endl;
		//if (bytesRead > 0) {
			//for (int i = 0; i < bytesRead; i++) {
				//m_readBuffer.push(buffer[i]);
				////std::cout << "pushing back: " << buffer[i] << std::endl;
			//}
		//}
	//}
//private:
	//SGIOChannel * m_channelSend;
	//SGIOChannel * m_channelReceive;
	//Mutex m_mutexSend;
	//Mutex m_mutexReceive;
	//SGBlockingQueue<uint8_t> m_readBuffer;
//};

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
