#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "Autopilot.hpp"

namespace apo
{
    
class Component
{
/*
 * methods
 */
public:
    Component() {};
    virtual ~Component() {};

    /**
     * This function updates the component, it is pure virtual so must be implemented.
     */
    virtual void update() = 0;

/*
 * attributes
 */
private:
    Autopilot * autopilot;

// accessors

protected:
    void getAutopilot();
    
};

};

#endif /* COMPONENT_HPP_ */

