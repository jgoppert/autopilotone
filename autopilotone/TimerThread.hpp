#ifndef AUTOPILOTONE_TIMER_HPP_
#define AUTOPILOTONE_TIMER_HPP_

#include "interfaces.hpp"

namespace autopilotone {

class TimerThread : public Thread {
public:
    TimerThread(float frequency, ProcessInterface * process, ClockInterface * clock) :
        m_periodMicros(1000000.0/frequency), m_running(false),
        m_process(process), m_clock(clock) {
        start();
    }
    void run() {
        if (get_process() == NULL) {
            return;
        }
        set_running(true);
        while(get_running()) {
            uint64_t start = get_clock()->get_micros();
            get_process()->update();
            uint64_t elapsed = get_clock()->get_micros() - start;
            if (elapsed < 0) {
                elapsed = get_periodMicros();
            } else if (elapsed > get_periodMicros()) {
                elapsed = get_periodMicros();
            }
            get_clock()->sleepMicros(get_periodMicros() - elapsed);
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
    uint64_t m_periodMicros;
    ProcessInterface * m_process;
    ClockInterface * m_clock;
    uint64_t m_start;
};

} // autopilotone

#endif // AUTOPILOTONE_TIMER_HPP_
