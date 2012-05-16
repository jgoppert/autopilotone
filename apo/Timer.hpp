#ifndef APO_TIMER_HPP_
#define APO_TIMER_HPP_

#include "interfaces.hpp"
#include <iostream>
namespace apo {

class Timer {
public:
    Timer(uint64_t periodMicros, ComponentInterface * component, ClockInterface * clock) :
            m_periodMicros(periodMicros), m_running(false),
            m_component(component), m_clock(clock) {
    }
    void start() {
        set_running(true);
        while(get_running()) {
            uint64_t start = get_clock()->get_micros();
            get_component()->update();
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
    }
protected:
    LOCKED_GET_SET(bool,running);
    ComponentInterface * get_component() { return m_component; }
    ClockInterface * get_clock() { return m_clock; }
    uint64_t get_periodMicros() { return m_periodMicros; }
private:
    LOCKED_ATTR(bool,running);
    uint64_t m_periodMicros;
    ComponentInterface * m_component;
    ClockInterface * m_clock;
};

} // apo

#endif // APO_TIMER_HPP_
