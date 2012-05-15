// Controller.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Controller.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Controller.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "interfaces.hpp"

namespace apo
{

class Controller : public ControllerInterface
{

// methods
public:
    Controller (NavigatorReadInterface * navigator, GuideReadInterface * guide) :
        m_navigator(navigator), m_guide(guide) {};
    virtual ~Controller() {};

protected:
    NavigatorReadInterface * getNavigator() { return m_navigator; }
    GuideReadInterface * getGuide() { return m_guide; }

    // component
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }

private:

    // interfaces
    DebugInterface * m_debug;
    NavigatorReadInterface * m_navigator;
    GuideReadInterface * m_guide;

}; // class Controller

    
}; // namespace apo


#endif /* CONTROLLER_HPP_ */

