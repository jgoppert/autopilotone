#ifndef AUTOPILOTONE_BOARDS_BOARD_TEST_HPP_
#define AUTOPILOTONE_BOARDS_BOARD_TEST_HPP_

#ifdef OS_PC // Running simulation on PC
#include "Board_Test_Sim.hpp"
#else // Running real software

#include "../autopilotone.hpp"

namespace autopilotone {

class Board_Test : public Board {
public:
    Board_Test() :
        m_clock(),
        m_serialPort(),
        m_debug()
    {
        // tell board what hardware is present
        set_clock(&m_clock);
        set_serialPort(&m_serialPort);
        set_debug(&m_debug);
    }
private:
    Clock m_clock;
    SerialPort m_serialPort;
    Debug m_debug;
};

}

#endif // OS

#endif /* AUTOPILOTONE_BOARDS_BOARD_TEST_HPP_ */
