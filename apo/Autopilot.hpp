// Autopilot.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Autopilot.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Autopilot.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef APO_AUTOPILOT_HPP_
#define APO_AUTOPILOT_HPP_

#include "interfaces.hpp"

namespace apo
{

class Autopilot {

// methods
public:
    Autopilot (NavigatorReadWriteInterface * navigator,
            GuideReadWriteInterface * guide,
            ControllerReadWriteInterface * controller,
            CommLinkReadWriteInterface * commLink) :
        m_navigator(navigator),
        m_guide(guide),
        m_controller(controller),
        m_commLink(commLink) {}; 
    virtual ~Autopilot() {};

protected:
    NavigatorReadWriteInterface * getNavigator() { return m_navigator; }
    GuideReadWriteInterface * getGuide() { return m_guide; }
    ControllerReadWriteInterface * getController() { return m_controller; }
    CommLinkReadWriteInterface * getCommLink() { return m_commLink; }

private:
    NavigatorReadWriteInterface * m_navigator;
    GuideReadWriteInterface * m_guide;
    ControllerReadWriteInterface * m_controller;
    CommLinkReadWriteInterface * m_commLink;
}; // class Autopilot

}; // namespace apo


#endif // APO_AUTOPILOT_HPP_

