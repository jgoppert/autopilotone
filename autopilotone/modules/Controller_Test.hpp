#ifndef AUTOPILOTONE_MODULES_CONTROLLER_TEST_HPP_
#define AUTOPILOTONE_MODULES_CONTROLLER_TEST_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class Controller_Test : public Controller {
public:
    Controller_Test(BoardInterface * board,
            NavigatorReadInterface * navigator,
            GuideReadInterface * guide) :
        Controller(board,navigator,guide) {}
    void update() {
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->writeString("controller update\n");
    }
};

}

#endif /* AUTOPILOTONE_MODULES_CONTROLLER_TEST_HPP_ */
