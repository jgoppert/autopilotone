#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class TestCommLink : public CommLink {
public:
    TestCommLink(NavigatorInterface * navigator, GuideInterface * guide,
            ControllerInterface * controller, DebugInterface * debug) : 
        CommLink(navigator,guide,controller,debug) {}
    void update() {
        get_navigator()->set_lat(1);
        get_debug()->send("commlink update");
    }
};

class TestNavigator : public Navigator {
public:
    TestNavigator() : Navigator() {}
    void update() {
        set_lon_degE7(10000);
        get_debug()->send("navigator update");
    }
};

class FlightGearNavigator : public Navigator {
public:
    FlightGearNavigator() : Navigator() {}
    void update() {
        set_lon_degE7(10000);
        get_debug()->send("navigator update");
    }
};

class TestGuide : public Guide {
public:
    TestGuide(NavigatorReadInterface * navigator) : Guide(navigator) {}
    void update() {
        get_navigator()->get_lat();
        get_debug()->send("guide update");
    }
};

class TestController : public Controller {
public:
    TestController(NavigatorReadInterface * navigator, GuideReadInterface * guide) : Controller(navigator,guide) {}
    void update() {
        get_navigator()->get_lat();
        get_debug()->send("controller update");
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
        float contFreq = 1.0;
        float guideFreq = 1.0;
        float commFreq = 1.0;

        Timer navigatorTimer(1000000.0/navFreq,get_navigator(),&clock);
        Timer controllerTimer(1000000.0/contFreq,get_controller(),&clock);
        Timer guideTimer(1000000.0/guideFreq,get_guide(),&clock);
        Timer commLinkTimer(1000000.0/commFreq,get_commLink(),&clock);

        // threads
        boost::thread thread1(boost::bind(&Timer::start,&commLinkTimer));
        boost::thread thread2(boost::bind(&Timer::start,&navigatorTimer));
        boost::thread thread3(boost::bind(&Timer::start,&guideTimer));
        boost::thread thread4(boost::bind(&Timer::start,&controllerTimer));

        // join threads
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
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

