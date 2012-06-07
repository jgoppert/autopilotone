#ifndef AUTOPILOTONE_MODULES_TESTNAVIGATOR_HPP_

#define AUTOPILOTONE_MODULES_TESTNAVIGATOR_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class TestNavigator : public Navigator {
public:
    TestNavigator(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->write("navigator update");
    }
};

}

#endif /* AUTOPILOTONE_MODULES_TESTNAVIGATOR_HPP_ */
