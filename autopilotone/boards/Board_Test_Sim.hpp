#ifndef AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_
#define AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class Board_Test_Sim : public Board {
public:
    static const uint16_t serialFreq = 100; /// Serial frequency Hz
    Board_Test_Sim() : m_clockInst(), m_serialInst(), m_debugInst(),
        m_serialThreadInst(serialFreq,&m_serialInst,&m_clockInst) {
        // tell board what hardware is present
        set_clock(&m_clockInst);
        set_serial(&m_serialInst);
        set_debug(&m_debugInst);
    }
private:
    Clock m_clockInst;
    Serial m_serialInst;
    Debug m_debugInst;
    TimerThread m_serialThreadInst;
};

}

#endif /* AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_ */
