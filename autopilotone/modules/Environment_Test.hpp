#ifndef AUTOPILOTONE_MODULES_ENVIRONMENT_TEST_HPP_
#define AUTOPILOTONE_MODULES_ENVIRONMENT_TEST_HPP_

#ifndef OS_PC
#error Environment can only be constructed on PC
#endif

#include <autopilotone/autopilotone.hpp>

namespace autopilotone {

class Environment_Test : public Environment {
public:
    Environment_Test(BoardInterface * board) :
        Environment(board) {}
    void update() {
        std::cout << "environment update" << std::endl;
    }
};

}

#endif /* AUTOPILOTONE_MODULES_ENVIRONMENT_TEST_HPP_ */
