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
    Guide (BoardInterface * board,
            NavigatorReadInterface * navigator) :
        m_board(board), m_navigator(navigator)
    {
        set_flightPlan( & m_flightPlanMaster);
    }; 
    virtual ~Guide() {};

    // read interface
    virtual FlightPlanInterface * get_flightPlan() 
    {
        return (m_flightPlan);
    };

    virtual guideMode_t get_mode() { return (m_guideMode); }

    virtual float get_latError_degFloat() { return (m_latError_degFloat); }
    virtual float get_lonError_degFloat() { return (m_lonError_degFloat); }
    virtual float get_altError_ftFloat() { return (m_altError_ftFloat); }

    // write interface
    virtual void set_flightPlan(FlightPlanInterface * flightPlan) {
        m_flightPlan = flightPlan;
    }

    virtual void set_mode(guideMode_t mode) { m_guideMode = mode; }

    virtual float update_error() {
        Command c = m_flightPlan->get_currentCommand();
        m_latError_degFloat = c.lat_degIntE7 - m_navigator->get_lat();
        m_lonError_degFloat = c.lon_degIntE7 - m_navigator->get_lon();
        m_altError_ftFloat = c.alt_degIntE3 - m_navigator->get_alt();
        return (0); // TODO return error
    }
    
protected:
    BoardInterface * get_board() { return (m_board); }
    NavigatorReadInterface * get_navigator() { return (m_navigator); }

    // component
    FlightPlan m_flightPlanMaster;
    guideMode_t m_guideMode;

    float m_latError_degFloat;
    float m_lonError_degFloat;
    float m_altError_ftFloat;

private:
    // interfaces
    BoardInterface * m_board;
    NavigatorReadInterface * m_navigator;
    FlightPlanInterface * m_flightPlan;

}; // class Guide

}; // namespace autopilotone


#endif /* GUIDE_HPP_ */

