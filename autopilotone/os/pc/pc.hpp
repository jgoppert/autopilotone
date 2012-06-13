#ifndef AUTOPILOTONE_OS_PC_PC_HPP_
#define AUTOPILOTONE_OS_PC_PC_HPP_

#include <iostream>
#include <string.h>
#include <stdexcept>
#include "../../interfaces.hpp"
#include <simgear/timing/timestamp.hxx>
#include <simgear/threads/SGQueue.hxx>
#include <simgear/io/sg_socket.hxx>

#ifdef USE_SGTHREADS
#include "sgthreads.hpp"
#else
#include "../generic/protothreads.hpp"
#endif

namespace autopilotone {

class Debug: public DebugInterface {
public:
    void write(const char * buf, uint32_t bytes) {
        ScopedLock lock(m_mutex);
        char buf2[bytes+1];
        strncpy(buf2,buf,bytes);
        buf2[bytes] = '\0';
        std::cout << buf2 << std::flush;
    }
    void writeString(const char * buf) {
        ScopedLock lock(m_mutex);
        std::cout << buf << std::flush;
    }
private:
    Mutex m_mutex;
};

class Clock: public ClockInterface {
public:
    Clock() :
        m_clock(SGTimeStamp::now()), m_mutex() {
    }
    void sleepMicros(uint64_t micros) {
        SGTimeStamp::sleepFor(SGTimeStamp::fromUSec(micros));
    }
    uint64_t get_micros() {
        ScopedLock lock(m_mutex);
        return((SGTimeStamp::now() - m_clock).toUSecs());
    }
private:
    Mutex m_mutex;
    SGTimeStamp m_clock;
};

class SerialPort: public SerialPortInterface {
public:
    SerialPort() :
        m_channelSend("127.0.0.1", "5001", "udp"),
        m_channelReceive("", "5002", "udp"),
        m_mutexSend(), m_mutexReceive(),
        m_readBuffer() {
        if (!m_channelSend.open(SG_IO_OUT)) {
            throw std::runtime_error("failed to connect send channel");
        }
        if (!m_channelReceive.open(SG_IO_IN)) {
            throw std::runtime_error("failed to connect receive channel");
        }
    }
    virtual ~SerialPort() {
        ScopedLock lockReceive(m_mutexReceive);
        ScopedLock lockSend(m_mutexSend);
        m_channelSend.close();
        m_channelReceive.close();
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
    void write(const char * c, uint32_t bytes) {
        ScopedLock lock(m_mutexSend);
        m_channelSend.write((const char *) c, bytes);
    }
    void writeString(const char * c) {
        ScopedLock lock(m_mutexSend);
        m_channelSend.writestring((const char *)c);
    }
    void update() {
        ScopedLock lock(m_mutexReceive);
        char buffer[100];
        int bytesRead = m_channelReceive.read(buffer, 100);
        //std::cout << "bytesRead : " << bytesRead << std::endl;
        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; i++) {
                m_readBuffer.push(buffer[i]);
                //std::cout << "pushing back: " << buffer[i] << std::endl;
            }
        }
    }
private:
    SGSocket m_channelSend;
    SGSocket m_channelReceive;
    Mutex m_mutexSend;
    Mutex m_mutexReceive;
    SGBlockingQueue<uint8_t> m_readBuffer;
};

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_PC_PC_HPP_
