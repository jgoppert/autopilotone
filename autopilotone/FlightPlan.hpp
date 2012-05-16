// FlightPlan.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// FlightPlan.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FlightPlan.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef AUTOPILOTONE_FLIGHT_PLAN_HPP_
#define AUTOPILOTONE_FLIGHT_PLAN_HPP_

#include "interfaces.hpp"
#include <vector>

#define COMMAND_BUFFER_SIZE 32

namespace autopilotone
{

class FlightPlan : public FlightPlanReadInterface {

// methods
public:
    FlightPlan () :
        m_debug(&nullDebug) { m_commandIndex = 0;}; 
    virtual ~FlightPlan() {};
    uint16_t get_currentCommandIndex() { return m_commandIndex; };
    

protected:

    // component
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }

private:
    // component
    Command m_commands [COMMAND_BUFFER_SIZE];
    uint16_t m_commandIndex;

    // interfaces
    DebugInterface * m_debug;

}; // class FlightPlan

}; // namespace apo


#endif /* AUTOPILOTONE_FLIGHTPLAN_HPP_ */ 
