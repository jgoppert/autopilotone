#ifndef AUTOPILOTONE_MODULES_TESTGUIDE_HPP_
#define AUTOPILOTONE_MODULES_TESTGUIDE_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class TestGuide : public Guide {
public:
    TestGuide(BoardInterface * board,
            NavigatorReadInterface * navigator) :
        Guide(board,navigator) {}
    void update() {
        float lat = get_navigator()->get_lat();
        get_board()->get_debug()->write("guide update");
    }
};

}

#endif /* AUTOPILOTONE_MODULES_TESTGUIDE_HPP_ */
