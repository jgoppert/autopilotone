#ifndef AUTOPILOTONE_OS_LINUX_HPP_
#define AUTOPILOTONE_OS_LINUX_HPP_

#include <iostream>
#include "../interfaces.hpp"
#include <simgear/timing/timestamp.hxx>
#include <simgear/threads/SGThread.hxx>
#include <simgear/threads/SGGuard.hxx>

namespace autopilotone {

class Mutex : public MutexInterface {
public:
    void lock() {
        return m_mutex.lock();
    }
    void unlock() {
        return m_mutex.unlock();
    }
private:
    SGMutex m_mutex;
};

class Debug : public DebugInterface {
public:
    void send(const std::string & str) {
        ScopedLock lock(m_mutex);
        std::cout << str << std::endl;
    }
private:
    Mutex m_mutex;
};

class Clock : public ClockInterface {
public:
    Clock() : m_clock(SGTimeStamp::now()) {
    }
    void sleepMicros(uint64_t micros) {
        SGTimeStamp::sleepFor(SGTimeStamp::fromUSec(micros));
    }
    uint64_t get_micros() {
        return (SGTimeStamp::now() - m_clock).toUSecs();
    }
private:
    SGTimeStamp m_clock;
}clock;

class Thread : public SGThread {
};

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_LINUX_HPP_
