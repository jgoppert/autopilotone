// Guide.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Guide.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Guide.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GUIDE_HPP_
#define GUIDE_HPP_

#include "interfaces.hpp"
#include "FlightPlan.hpp"
#include <vector>

namespace autopilotone
{

class Guide : public GuideInterface {

// methods
public:
    Guide (NavigatorReadInterface * navigator) :
        m_navigator(navigator), m_debug(&nullDebug)
    {
        set_flightPlan( & m_flightPlanMaster);
    }; 
    virtual ~Guide() {};

    // read interface
    virtual FlightPlanInterface * get_flightPlan() 
    {
        return m_flightPlan;
    };

    virtual guideMode_t get_mode() { return m_guideMode; }

    // write interface
    virtual void set_flightPlan(FlightPlanInterface * flightPlan) {
        m_flightPlan = flightPlan;
    }

    virtual void set_mode(guideMode_t mode) { m_guideMode = mode; }
    
protected:
    NavigatorReadInterface * getNavigator() { return m_navigator; }

    // component
    FlightPlan m_flightPlanMaster;
    guideMode_t m_guideMode;

    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }


private:

    // interfaces
    FlightPlanInterface * m_flightPlan;
    DebugInterface * m_debug;
    NavigatorReadInterface * m_navigator;

}; // class Guide

}; // namespace autopilotone


#endif /* GUIDE_HPP_ */

