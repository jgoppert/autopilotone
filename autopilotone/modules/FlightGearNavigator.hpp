#ifndef AUTOPILOTONE/MODULES/FLIGHTGEARNAVIGATOR_HPP_
#define AUTOPILOTONE/MODULES/FLIGHTGEARNAVIGATOR_HPP_

#include "autopilotone/autopilotone.hpp"

namespace autopilotone {

class FlightGearNavigator : public Navigator {
public:
    FlightGearNavigator(BoardInterface * board) :
        Navigator(board) {}
    void update() {
        set_lon_degE7(10000);
        float lon = get_lon_degE7();
        get_board()->get_debug()->write("navigator update");
    }
};

}

#endif /* AUTOPILOTONE/MODULES/FLIGHTGEARNAVIGATOR_HPP_ */
