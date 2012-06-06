#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

Serial serial1;

class TestCommLink : public CommLink {
public:
    TestCommLink(NavigatorInterface * navigator, GuideInterface * guide,
            ControllerInterface * controller, DebugInterface * debug) : 
        CommLink(navigator,guide,controller,debug) {}
    void update() {
        get_navigator()->set_lat(1);
        //get_debug()->send("commlink update");
    }
};

class TestNavigator : public Navigator {
public:
    TestNavigator() : Navigator() {}
    void update() {
        set_lon_degE7(10000);
        //get_debug()->send("navigator update");
        const char * message = "hello";
        serial1.write((const uint8_t *)message,sizeof(message));
        while (serial1.available() > 0) {
            get_debug()->send("got: ");
            get_debug()->send((const char *)serial1.read());
        }

    }
};

class FlightGearNavigator : public Navigator {
public:
    FlightGearNavigator() : Navigator() {}
    void update() {
        set_lon_degE7(10000);
        //get_debug()->send("navigator update");
    }
};

class TestGuide : public Guide {
public:
    TestGuide(NavigatorReadInterface * navigator) : Guide(navigator) {}
    void update() {
        get_navigator()->get_lat();
        //get_debug()->send("guide update");
    }
};

class TestController : public Controller {
public:
    TestController(NavigatorReadInterface * navigator, GuideReadInterface * guide) : Controller(navigator,guide) {}
    void update() {
        get_navigator()->get_lat();
        //get_debug()->send("controller update");
    }
};

class TestAutopilot : public Autopilot {
public:
    TestAutopilot(NavigatorInterface * navigator,
            GuideInterface * guide,
            ControllerInterface * controller,
            CommLinkInterface * commLink) :
        Autopilot(navigator,guide,controller,commLink)
    {
        float navFreq = 100.0;
        float contFreq = 50.0;
        float guideFreq = 10.0;
        float commFreq = 1.0;

        /**
         * should be moved to sim board
         */
        uint16_t serialFreq = 100;
        TimerThread serialThread(1000000.0/serialFreq,&serial1,&clock);
        TimerThread navigatorThread(1000000.0/navFreq,get_navigator(),&clock);
        TimerThread controllerThread(1000000.0/contFreq,get_controller(),&clock);
        TimerThread guideThread(1000000.0/guideFreq,get_guide(),&clock);
        TimerThread commLinkThread(1000000.0/commFreq,get_commLink(),&clock);

        // join threads
        navigatorThread.join();
        controllerThread.join();
        guideThread.join();
        commLinkThread.join();
        serialThread.join();
    }
};

} // namespace autopilotone

int main (int argc, char const* argv[])
{
    using namespace autopilotone;
    TestNavigator navigator;
    TestGuide guide(&navigator);
    TestController controller(&navigator,&guide);
    Debug debug;
    TestCommLink commLink(&navigator,&guide,&controller,&debug);
    TestAutopilot(&navigator,&guide,&controller,&commLink);
    return 0;
};

