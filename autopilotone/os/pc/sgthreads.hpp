#ifndef AUTOPILOTONE_OS_PC_SGTHREADS_HPP_
#define AUTOPILOTONE_OS_PC_SGTHREADS_HPP_

#include "../../interfaces.hpp"
#include <simgear/threads/SGThread.hxx>
#include <simgear/threads/SGGuard.hxx>

namespace autopilotone {

class Mutex: public MutexInterface {
public:
    void lock() {
        m_mutex.lock();
    }
    void unlock() {
        m_mutex.unlock();
    }
private:
    SGMutex m_mutex;
};

class Thread: public SGThread {
};

class TimerThread : public Thread {
public:
    TimerThread(float frequency, ProcessInterface * process, ClockInterface * clock) :
        m_periodMicros(1000000.0/frequency), m_running(false),
        m_start(), m_elapsed(),
        m_process(process), m_clock(clock) {
        start();
    }
    void run() {
        if (get_process() == NULL) {
            return;
        }
        set_running(true);
        while(get_running()) {
            m_start = get_clock()->get_micros();
            get_process()->update();
            m_elapsed = get_clock()->get_micros() - m_start;
            if (m_elapsed < 0) {
                m_elapsed = get_periodMicros();
            } else if (m_elapsed > get_periodMicros()) {
                m_elapsed = get_periodMicros();
            }
            get_clock()->sleepMicros(get_periodMicros() - m_elapsed);
        }
    }
    void stop() {
        set_running(false);
        join();
    }
    virtual ~TimerThread() {
        stop();
    }
protected:
    LOCKED_GET_SET(bool,running);
    ProcessInterface * get_process() {
        return m_process;
    }
    ClockInterface * get_clock() {
        return m_clock;
    }
    uint64_t get_periodMicros() {
        return m_periodMicros;
    }
private:
    LOCKED_ATTR(bool,running);
    uint64_t m_start;
    uint64_t m_elapsed;
    uint64_t m_periodMicros;
    ProcessInterface * m_process;
    ClockInterface * m_clock;
};

// not necessary for simgear threads
class Scheduler {
public:
    void run() {};
} scheduler;

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_PC_SGTHREADS_HPP_
