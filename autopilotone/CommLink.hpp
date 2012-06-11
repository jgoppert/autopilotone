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
    CommLink(BoardInterface * board,
             NavigatorInterface * navigator,
             GuideInterface * guide,
             ControllerInterface * controller) :
        m_board(board),
        m_navigator(navigator),
        m_guide(guide),
        m_controller(controller)
    {
    };
    virtual ~CommLink() {};

protected:
    BoardInterface * get_board() {
        return(m_board);
    }
    NavigatorInterface * get_navigator() {
        return(m_navigator);
    }
    GuideInterface * get_guide() {
        return(m_guide);
    }
    ControllerInterface * get_controller() {
        return(m_controller);
    }

private:
    BoardInterface * m_board;
    NavigatorInterface * m_navigator;
    GuideInterface * m_guide;
    ControllerInterface * m_controller;

}; // class CommLink

} // namespace autopilotone


#endif /* COMMLINK_HPP_ */

