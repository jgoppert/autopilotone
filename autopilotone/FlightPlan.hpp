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
#include "macros.hpp"
#include <vector>

#define COMMAND_BUFFER_SIZE 32

namespace autopilotone
{

class FlightPlan : public FlightPlanInterface {

// methods
public:
    FlightPlan () :
        m_debug(&nullDebug) { m_commandIndex = 0;}; 
    virtual ~FlightPlan() {};

    // read interface
    virtual uint16_t get_currentCommandIndex() { return m_commandIndex; }
    virtual uint16_t get_lastCommandIndex() { return m_commandIndex-1; }
    virtual uint16_t get_nextCommandIndex() { return m_commandIndex+1; }
    virtual uint16_t get_commandCount() { return m_commandHighestIndex+1; }
    virtual Command get_command(uint16_t index)
    {
        blockingTestAndSet_commandAccessFlag();
        return index > m_commandHighestIndex ? m_commands[m_commandHighestIndex] : m_commands[index];
        clear_commandAccessFlag();
    }
    virtual Command get_currentCommand()
    {
        blockingTestAndSet_commandAccessFlag();
        return m_commands[m_commandIndex];
        clear_commandAccessFlag();
    }

    // write interface
    virtual void addWaypoint(uint16_t index, Command waypoint) 
    {

        blockingTestAndSet_commandAccessFlag();
        if(index > m_commandHighestIndex)
        {
            m_commandHighestIndex++;
            m_commands[m_commandHighestIndex] = waypoint;
        }
        else
        {
            m_commands[index] = waypoint;
        }
        clear_commandAccessFlag();
    }

    virtual void removeWaypoint(uint16_t index)
    {
        blockingTestAndSet_commandAccessFlag();
        if(index > m_commandHighestIndex)
        {
            return;
        }

        // If deleting the last command, drop the current index to the
        // new last.
        if(index == m_commandIndex)
        {
            index--;
        }


        m_commandHighestIndex--;
        for(; index < m_commandHighestIndex; index++)
        {
            m_commands[index] = m_commands[index+1];
        }
        clear_commandAccessFlag();
    }

    virtual void clearWaypoints()
    {
        blockingTestAndSet_commandAccessFlag();
        m_commandHighestIndex = -1;
        m_commandIndex = -1;
        clear_commandAccessFlag();
    }

protected:

    // component
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }

    // component
    Command m_commands [COMMAND_BUFFER_SIZE];
    uint16_t m_commandIndex;
    uint16_t m_commandHighestIndex;

    COMPLETE_TEST_AND_SET(commandAccessFlag, 25);

private:

    LOCKED_FLAG(commandAccessFlag);
    // interfaces
    DebugInterface * m_debug;

}; // class FlightPlan

}; // namespace apo


#endif /* AUTOPILOTONE_FLIGHTPLAN_HPP_ */ 
