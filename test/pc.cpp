#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class TestCommLink : public CommLink {
public:
    TestCommLink(BoardInterface * board,
            NavigatorInterface * navigator,
            GuideInterface * guide,
            ControllerInterface * controller) : 
        CommLink(board,navigator,guide,controller) {}
    void update() {
        get_navigator()->set_lat(1);
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->write("comm update");
        //const char * message = "hello123456789";
        //get_board()->get_serial()->write((const uint8_t *)message,14);
        //while (get_board()->get_serial()->available() > 0) {
            //char c = get_board()->get_serial()->read();
            //std::cout << c;
            //if (get_board()->get_serial()->available() == 0) std::cout << std::endl;
        //}
    }
};

class TestNavigator : public Navigator {
public:
    TestNavigator(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->write("navigator update");
    }
};

class FlightGearNavigator : public Navigator {
public:
    FlightGearNavigator(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->write("navigator update");
    }
};

class TestGuide : public Guide {
public:
    TestGuide(BoardInterface * board,
            NavigatorReadInterface * navigator) :
        Guide(board,navigator) {}
    void update() {
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->write("guide update");
    }
};

class TestController : public Controller {
public:
    TestController(BoardInterface * board,
            NavigatorReadInterface * navigator,
            GuideReadInterface * guide) :
        Controller(board,navigator,guide) {}
    void update() {
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->write("controller update");
    }
};

class TestAutopilot : public Autopilot {
public:
    static uint64_t freq2micros(float freq) {
        return(1000000.0/freq); 
    }
    TestAutopilot(BoardInterface * board,
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
        get_board()->get_debug()->write("initialize autopilot");
    }
private:
    TimerThread m_navigatorThread;
    TimerThread m_guideThread;
    TimerThread m_controllerThread;
    TimerThread m_commLinkThread;
};

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

} // namespace autopilotone

int main (int argc, char const* argv[])
{
    using namespace autopilotone;
    TestBoardSim board;
    TestNavigator navigator(&board);
    TestGuide guide(&board,&navigator);
    TestController controller(&board,&navigator,&guide);
    TestCommLink commLink(&board,&navigator,&guide,&controller);
    TestAutopilot(&board,&navigator,1,&guide,1,&controller,1,&commLink,1);
    return(0);
};

