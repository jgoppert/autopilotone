// Board.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Board.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Board.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef AUTOPILOTONE_BOARD_HPP_
#define AUTOPILOTONE_BOARD_HPP_ 

#include "interfaces.hpp"

namespace autopilotone {

class Board : public BoardInterface
{
public:
    Board() :
        m_clock(&nullClock), m_serial(&nullSerial), m_debug(&nullDebug) {};
    virtual ~Board() {};

    ClockInterface * get_clock() { return m_clock; }
    SerialInterface * get_serial() { return m_serial; }
    DebugInterface * get_debug() { return m_debug; }

protected:
    void set_clock(ClockInterface * clock) { m_clock = clock; }
    void set_serial(SerialInterface * serial) { m_serial = serial; }
    void set_debug(DebugInterface * debug) { m_debug = debug; }

private:
    ClockInterface * m_clock;
    SerialInterface * m_serial;
    DebugInterface * m_debug;
};

};

#endif /* AUTOPILOTONE_BOARD_HPP_ */
