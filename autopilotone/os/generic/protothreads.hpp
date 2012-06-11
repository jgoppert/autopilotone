#ifndef AUTOPILOTONE_OS_GENERIC_PROTOTHREADS_HPP_
#define AUTOPILOTONE_OS_GENERIC_PROTOTHREADS_HPP_

#include <vector>
#include <pt.h>

namespace autopilotone {

// no need for protothreads, single threaded
class Mutex: public MutexInterface {
public:
    Mutex() {
    }
    void lock() {
    }
    void unlock() {
    }

private:
    //bool lockFlag;
};

struct ThreadInterface_PT : public ThreadInterface, public pt {
    ThreadInterface_PT() : pt() {
    }
    virtual int pt_run() = 0;
};

class Scheduler {
public:
    /**
     * A simple round robin scheduling system
     */
    int run() {
        for (int i=0; i<m_threads.size(); i++) {
            m_threads[i]->pt_run();
        }
    }
    void addThread(ThreadInterface_PT * thread) {
        m_threads.push_back(thread);
    }
private:
    std::vector<ThreadInterface_PT *> m_threads;
} scheduler;


class TimerThread : public ThreadInterface_PT {
public:
    TimerThread(float frequency, ProcessInterface * process, ClockInterface * clock) :
        m_periodMicros(1000000.0/frequency), m_running(false),
        m_start(), m_timestamp(),
        m_process(process), m_clock(clock) {
        PT_INIT(this);
        start();
    }
    void start() {
        scheduler.addThread(this);
    }
    void join() {
    }
    int pt_run() {
        PT_BEGIN(this);
        while(1) {
            PT_WAIT_UNTIL(this, get_clock()->get_micros() - m_timestamp > m_periodMicros);
            m_timestamp = get_clock()->get_micros();
            get_process()->update();
        }
        PT_END(this);
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
    uint64_t m_periodMicros;
    LOCKED_ATTR(volatile bool,running);
    uint64_t m_start;
    uint32_t m_timestamp;
    ProcessInterface * m_process;
    ClockInterface * m_clock;
};


} // namespace autopilotone

#endif // AUTOPILOTONE_OS_THREADS_PROTOTHREADS_HPP_
