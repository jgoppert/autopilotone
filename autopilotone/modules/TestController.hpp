#ifndef AUTOPILOTONE_MODULES_TESTCONTROLLER_HPP_
#define AUTOPILOTONE_MODULES_TESTCONTROLLER_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

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

}

#endif /* AUTOPILOTONE_MODULES_TESTCONTROLLER_HPP_ */
