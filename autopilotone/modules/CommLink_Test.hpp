#ifndef AUTOPILOTONE_MODULES_COMMLINK_TEST_HPP_
#define AUTOPILOTONE_MODULES_COMMLINK_TEST_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class CommLink_Test : public CommLink {
public:
    CommLink_Test(BoardInterface * board,
            NavigatorInterface * navigator,
            GuideInterface * guide,
            ControllerInterface * controller) : 
        CommLink(board,navigator,guide,controller) {}
    void update() {
        get_navigator()->set_lat(1);
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->writeString("comm update\n");
        get_board()->get_serial()->writeString("hello12345678\n");
        while (get_board()->get_serial()->available() > 0) {
            char c = get_board()->get_serial()->read();
            get_board()->get_debug()->write(&c,1);
        }
    }
};

}

#endif /* AUTOPILOTONE_MODULES_COMMLINK_TEST_HPP_ */
