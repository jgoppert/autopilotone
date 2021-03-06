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

namespace autopilotone
{

class Controller : public ControllerInterface
{

// methods
public:
    Controller (BoardInterface * board,
                NavigatorReadInterface * navigator,
                GuideReadInterface * guide) :
        m_board(board),
        m_navigator(navigator),
        m_guide(guide) {};
    virtual ~Controller() {};

protected:
    BoardInterface * get_board() {
        return(m_board);
    }
    NavigatorReadInterface * get_navigator() {
        return(m_navigator);
    }
    GuideReadInterface * get_guide() {
        return(m_guide);
    }

private:
    BoardInterface * m_board;
    NavigatorReadInterface * m_navigator;
    GuideReadInterface * m_guide;

}; // class Controller


}; // namespace autopilotone


#endif /* CONTROLLER_HPP_ */

