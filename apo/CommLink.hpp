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

namespace apo
{

class CommLink : public CommLinkReadWriteInterface {

// methods
public:
    CommLink(Navigator * navigator) : m_navigator(navigator) {};
    virtual ~CommLink() {};

protected:
    NavigatorReadWriteInterface * getNavigator() { return m_navigator; }
    GuideReadWriteInterface * getGuide() { return m_guide; }
    ControllerReadWriteInterface * getController() { return m_controller; }

private:
    NavigatorReadWriteInterface * m_navigator;
    GuideReadWriteInterface * m_guide;
    ControllerReadWriteInterface * m_controller;
        
}; // class CommLink

} // namespace apo


#endif /* COMMLINK_HPP_ */

