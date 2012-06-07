#include <autopilotone/autopilotone.hpp>
#include <autopilotone/modules/TestNavigator.hpp>
#include <autopilotone/modules/TestGuide.hpp>
#include <autopilotone/modules/TestController.hpp>
#include <autopilotone/modules/TestCommLink.hpp>
#include <autopilotone/modules/TestAutopilot.hpp>
#include <autopilotone/boards/TestBoardSim.hpp>

int main (int argc, char const* argv[])
{
    using namespace autopilotone;
    TestBoardSim board;
    TestNavigator navigator(&board);
    TestGuide guide(&board,&navigator);
    TestController controller(&board,&navigator,&guide);
    TestCommLink commLink(&board,&navigator,&guide,&controller);
    TestAutopilot(&board,&navigator,10,&guide,2,&controller,5,&commLink,1);
    return(0);
};

