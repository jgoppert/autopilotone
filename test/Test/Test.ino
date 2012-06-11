#include <autopilotone/autopilotone.hpp>
#include <autopilotone/modules/Navigator_Test.hpp>
#include <autopilotone/modules/Guide_Test.hpp>
#include <autopilotone/modules/Controller_Test.hpp>
#include <autopilotone/modules/CommLink_Test.hpp>
//#include <autopilotone/modules/CommLink_MAVLink.hpp>
#include <autopilotone/modules/Autopilot_Test.hpp>
#include <autopilotone/boards/Board_Test.hpp>
#include <autopilotone/os/os.hpp>

namespace autopilotone {
// components
Board_Test board;
Navigator_Test navigator(&board);
Guide_Test guide(&board,&navigator);
Controller_Test controller(&board,&navigator,&guide);
CommLink_Test commLink(&board,&navigator,&guide,&controller);
Autopilot_Test autopilot(&board,&navigator,10,&guide,2,&controller,5,&commLink,1);
//CommLink_MAVLink commLink(0,0,MAV_TYPE_GENERIC,
        //&board,&navigator,&guide,&controller);
}

void setup() {
#ifdef OS_ARDUINO
    Serial.begin(115200);
#endif
}

void loop() {
    autopilotone::scheduler.run(); 
}
