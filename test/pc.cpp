#include <iostream>
#include <apo/apo.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include "apo/Autopilot.hpp"

namespace apo {

class TestCommLink : public CommLink {
public:
    TestCommLink(Navigator * navigator) : 
        CommLink(navigator) {}
    void update() {
        getNavigator()->set(NAV_INT32_LAT_DEGE7,1000);
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
};

class TestNavigator : public Navigator {
public:
    TestNavigator() : Navigator() {}
    void update() {
        set(NAV_INT32_LAT_DEGE7,1000);
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
};

class TestGuide : public Guide {
public:
    TestGuide() : Guide() {}
    void update() {
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
};

class TestController : public Controller {
public:
    TestController() : Controller() {}
    void update() {
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
};

class TestAutopilot : public Autopilot {
public:
    TestAutopilot(NavigatorReadWriteInterface * navigator,
            GuideReadWriteInterface * guide,
            ControllerReadWriteInterface * controller,
            CommLinkReadWriteInterface * commLink) :
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
        for (int i=0;i<100;i++) { std::cout << "commlink update " << i << std::endl;
            getCommLink()->update();
        }
    }

    void updateNavigator() {
        for (int i=0;i<100;i++) {
            std::cout << "navigator update " << i << std::endl;
            getNavigator()->update();
        }
    }

    void updateGuide() {
        for (int i=0;i<100;i++) {
            std::cout << "guide update " << i << std::endl;
            getGuide()->update();
        }
    }

    void updateController() {
        for (int i=0;i<100;i++) {
            std::cout << "controller update " << i << std::endl;
            getController()->update();
        }
    }
};

} // namespace apo

int main (int argc, char const* argv[])
{
    using namespace apo;
    TestNavigator navigator;
    TestGuide guide;
    TestController controller;
    TestCommLink commLink(&navigator);
    TestAutopilot(&navigator,&guide,&controller,&commLink);
    return 0;
};

