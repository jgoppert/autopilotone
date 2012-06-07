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
        get_board()->get_debug()->write("comm update");
        const char * message = "hello123456789";
        get_board()->get_serial()->write((const uint8_t *)message,14);
        while (get_board()->get_serial()->available() > 0) {
            char c = get_board()->get_serial()->read();
            std::cout << c;
            if (get_board()->get_serial()->available() == 0) std::cout << std::endl;
        }
    }
};

}

#endif /* AUTOPILOTONE_MODULES_COMMLINK_TEST_HPP_ */
