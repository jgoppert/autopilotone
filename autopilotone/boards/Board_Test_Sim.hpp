#ifndef AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_
#define AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_

#include "../autopilotone.hpp"
#include "../modules/Environment_JSBSim.hpp"

namespace autopilotone {

class Board_Test_Sim : public Board {
public:
    static const uint16_t serialFreq = 100; /// Serial frequency Hz
    static const uint16_t environmentFreq = 1; /// Environment frequency Hz
    Board_Test_Sim() :
        m_clock(),
        m_serialPort(),
        m_debug(),
        m_environment(this),
        m_serialThread(serialFreq,&m_serialPort,&m_clock),
        m_environmentThread(environmentFreq,&m_environment,&m_clock)
    {
        // tell board what hardware is present
        set_clock(&m_clock);
        set_serialPort(&m_serialPort);
        set_debug(&m_debug);
        set_environment(&m_environment);
    }
private:
    Clock m_clock;
    SerialPort m_serialPort;
    Debug m_debug;
    Environment_JSBSim m_environment;
    TimerThread m_serialThread;
    TimerThread m_environmentThread;
};

typedef Board_Test_Sim Board_Test;

}

#endif /* AUTOPILOTONE_BOARDS_BOARD_TEST_SIM_HPP_ */
