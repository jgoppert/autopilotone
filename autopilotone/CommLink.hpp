// CommLink.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// CommLink.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CommLink.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COMMLINK_HPP_
#define COMMLINK_HPP_

#include "interfaces.hpp"

namespace autopilotone
{

class CommLink : public CommLinkInterface {

// methods
public:
    CommLink(NavigatorInterface * navigator, GuideInterface * guide,
            ControllerInterface * controller, DebugInterface * debug) : 
        m_navigator(navigator),
        m_guide(guide), 
        m_controller(controller),
        m_debug(debug)
    {
        get_navigator()->set_debug(get_debug());
        get_guide()->set_debug(get_debug());
        get_controller()->set_debug(get_debug());
    };
    virtual ~CommLink() {};

protected:

    // interfaces
    NavigatorInterface * get_navigator() { return m_navigator; }
    GuideInterface * get_guide() { return m_guide; }
    ControllerInterface * get_controller() { return m_controller; }

    // component
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    DebugInterface * get_debug() { return m_debug; }

private:
    // interfaces
    NavigatorInterface * m_navigator;
    GuideInterface * m_guide;
    ControllerInterface * m_controller;
    DebugInterface * m_debug;
        
}; // class CommLink

} // namespace autopilotone


#endif /* COMMLINK_HPP_ */

