#include <autopilotone/autopilotone.hpp>
#include <autopilotone/modules/Navigator_Test.hpp>
#include <autopilotone/modules/Guide_Test.hpp>
#include <autopilotone/modules/Controller_Test.hpp>
#include <autopilotone/modules/CommLink_Test.hpp>
#include <autopilotone/modules/Autopilot_Test.hpp>
#include <autopilotone/boards/Board_Test_Sim.hpp>

int main (int argc, char const* argv[])
{
    using namespace autopilotone;
    Board_Test_Sim board;
    Navigator_Test navigator(&board);
    Guide_Test guide(&board,&navigator);
    Controller_Test controller(&board,&navigator,&guide);
    CommLink_Test commLink(&board,&navigator,&guide,&controller);
    Autopilot_Test(&board,&navigator,10,&guide,2,&controller,5,&commLink,1);
    return(0);
};

