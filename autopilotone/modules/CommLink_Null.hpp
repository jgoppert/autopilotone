#ifndef AUTOPILOTONE_MODULES_COMMLINK_NULL_HPP_
#define AUTOPILOTONE_MODULES_COMMLINK_NULL_HPP_

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class CommLink_Null : public CommLink {
public:
    CommLink_Null(BoardInterface * board,
            NavigatorInterface * navigator,
            GuideInterface * guide,
            ControllerInterface * controller) : 
        CommLink_Null(board,navigator,guide,controller) {}
    void update() {
    }
};

}

#endif /* AUTOPILOTONE_MODULES_COMMLINK_NULL_HPP_ */
