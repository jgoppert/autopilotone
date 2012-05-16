#include <apo/apo.hpp>

namespace apo {

class TestCommLink : public CommLink {
public:
    TestCommLink(NavigatorInterface * navigator, GuideInterface * guide,
            ControllerInterface * controller, DebugInterface * debug) : 
        CommLink(navigator,guide,controller,debug) {}
    void update() {
        getNavigator()->set_lat(1);
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

class TestGuide : public Guide {
public:
    TestGuide(NavigatorReadInterface * navigator) : Guide(navigator) {}
    void update() {
        getNavigator()->get_lat();
        get_debug()->send("guide update");
    }
};

class TestController : public Controller {
public:
    TestController(NavigatorReadInterface * navigator, GuideReadInterface * guide) : Controller(navigator,guide) {}
    void update() {
        getNavigator()->get_lat();
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

        Timer navigatorTimer(1000000.0/navFreq,getNavigator(),&clock);
        Timer controllerTimer(1000000.0/contFreq,getController(),&clock);
        Timer guideTimer(1000000.0/guideFreq,getGuide(),&clock);
        Timer commLinkTimer(1000000.0/commFreq,getCommLink(),&clock);

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

} // namespace apo

int main (int argc, char const* argv[])
{
    using namespace apo;
    TestNavigator navigator;
    TestGuide guide(&navigator);
    TestController controller(&navigator,&guide);
    Debug debug;
    TestCommLink commLink(&navigator,&guide,&controller,&debug);
    TestAutopilot(&navigator,&guide,&controller,&commLink);
    return 0;
};

