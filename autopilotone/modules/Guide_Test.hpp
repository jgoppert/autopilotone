#ifndef AUTOPILOTONE_MODULES_GUIDE_TEST_HPP_
#define AUTOPILOTONE_MODULES_GUIDE_TEST_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class Guide_Test : public Guide {
public:
    Guide_Test(BoardInterface * board,
            NavigatorReadInterface * navigator) :
        Guide(board,navigator) {}
    void update() {
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->write("guide update",12);
    }
};

}

#endif /* AUTOPILOTONE_MODULES_GUIDE_TEST_HPP_ */
