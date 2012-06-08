#ifndef AUTOPILOTONE_MODULES_AUTOPILOT_TEST_HPP_
#define AUTOPILOTONE_MODULES_AUTOPILOT_TEST_HPP_

#include <autopilotone/autopilotone.hpp>

namespace  autopilotone {

class Autopilot_Test : public Autopilot {
public:
    static uint64_t freq2micros(float freq) {
        return(1000000.0/freq); 
    }
    Autopilot_Test(BoardInterface * board,
            NavigatorInterface * navigator, float navFreq,
            GuideInterface * guide, float guideFreq,
            ControllerInterface * controller, float contFreq,
            CommLinkInterface * commLink, float commFreq) :
        Autopilot(board,navigator,guide,controller,commLink), 
        m_navigatorThread(navFreq,navigator,board->get_clock()),
        m_guideThread(guideFreq,guide,board->get_clock()),
        m_controllerThread(contFreq,controller,board->get_clock()),
        m_commLinkThread(commFreq,commLink,board->get_clock())
    {
        get_board()->get_debug()->writeString("initialize autopilot\n");
    }
private:
    TimerThread m_navigatorThread;
    TimerThread m_guideThread;
    TimerThread m_controllerThread;
    TimerThread m_commLinkThread;
};

}

#endif /* AUTOPILOTONE/MODULES/AUTOPILOT_TEST_HPP_ */
