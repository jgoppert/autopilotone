#ifndef AUTOPILOTONE_BOARDS_TESTBOARDSIM_HPP_
#define AUTOPILOTONE_BOARDS_TESTBOARDSIM_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class TestBoardSim : public Board {
public:
    static const uint16_t serialFreq = 100; /// Serial frequency Hz
    TestBoardSim() : m_clock(), m_serial(), m_debug(),
        m_serialThread(serialFreq,&m_serial,&m_clock) {
        // tell board what hardware is present
        set_clock(&m_clock);
        set_serial(&m_serial);
        set_debug(&m_debug);
    }
private:
    Clock m_clock;
    Serial m_serial;
    Debug m_debug;
    TimerThread m_serialThread;
};

}

#endif /* AUTOPILOTONE_BOARDS_TESTBOARDSIM_HPP_ */
