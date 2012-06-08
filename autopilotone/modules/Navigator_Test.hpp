#ifndef AUTOPILOTONE_MODULES_NAVIGATOR_TEST_HPP_
#define AUTOPILOTONE_MODULES_NAVIGATOR_TEST_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class Navigator_Test : public Navigator {
public:
    Navigator_Test(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->writeString("navigator update\n");
    }
};

}

#endif /* AUTOPILOTONE_MODULES_NAVIGATOR_TEST_HPP_ */
