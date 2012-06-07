#ifndef AUTOPILOTONE_MODULES_FLIGHTGEARNAVIGATOR_HPP_
#define AUTOPILOTONE_MODULES_FLIGHTGEARNAVIGATOR_HPP_

#include "autopilotone/autopilotone.hpp"

namespace autopilotone {

class Navigator_FlightGear : public Navigator {
public:
    Navigator_FlightGear(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->write("navigator update");
    }
};

}

#endif /* AUTOPILOTONE_MODULES_NAVIGATOR_FLIGHTGEAR_HPP_ */
