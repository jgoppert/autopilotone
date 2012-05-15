#include <apo/apo.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include "apo/Autopilot.hpp"

namespace apo {

class TestCommLink : public CommLink {
public:
    TestCommLink(NavigatorInterface * navigator, GuideInterface * guide,
            ControllerInterface * controller, DebugInterface * debug) : 
        CommLink(navigator,guide,controller,debug) {}
    void update() {
        getNavigator()->set(NAV_INT32_LAT_DEGE7,1000);
        getDebug()->send("commlink update");
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
};

class TestNavigator : public Navigator {
public:
    TestNavigator() : Navigator() {}
    void update() {
        set(NAV_INT32_LAT_DEGE7,1000);
        getDebug()->send("navigator update");
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
};

class TestGuide : public Guide {
public:
    TestGuide(NavigatorReadInterface * navigator) : Guide(navigator) {}
    void update() {
        getDebug()->send("guide update");
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
};

class TestController : public Controller {
public:
    TestController(NavigatorReadInterface * navigator, GuideReadInterface * guide) : Controller(navigator,guide) {}
    void update() {
        getDebug()->send("controller update");
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
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
        // threads
        boost::thread thread1(boost::bind(&TestAutopilot::updateComm,this));
        boost::thread thread2(boost::bind(&TestAutopilot::updateNavigator,this));
        boost::thread thread3(boost::bind(&TestAutopilot::updateGuide,this));
        boost::thread thread4(boost::bind(&TestAutopilot::updateController,this));

        // join threads
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
    }

    void updateComm() {
        for (int i=0;i<100;i++) {
            getCommLink()->update();
        }
    }

    void updateNavigator() {
        for (int i=0;i<100;i++) {
            getNavigator()->update();
        }
    }

    void updateGuide() {
        for (int i=0;i<100;i++) {
            getGuide()->update();
        }
    }

    void updateController() {
        for (int i=0;i<100;i++) {
            getController()->update();
        }
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

