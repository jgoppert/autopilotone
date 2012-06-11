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
        m_clock(), m_serialPort(), m_debug(), m_environment() {};
    virtual ~Board() {};

    ClockInterface * get_clock() {
        return m_clock;
    }
    SerialPortInterface * get_serialPort() {
        return m_serialPort;
    }
    DebugInterface * get_debug() {
        return m_debug;
    }
    EnvironmentReadInterface * get_environment() {
        return m_environment;
    }

protected:
    void set_clock(ClockInterface * clock) {
        m_clock = clock;
    }
    void set_serialPort(SerialPortInterface * serialPort) {
        m_serialPort = serialPort;
    }
    void set_debug(DebugInterface * debug) {
        m_debug = debug;
    }
    void set_environment(EnvironmentReadInterface * environment) {
        m_environment = environment;
    }

private:
    ClockInterface * m_clock;
    SerialPortInterface * m_serialPort;
    DebugInterface * m_debug;
    EnvironmentReadInterface * m_environment;
};

};

#endif /* AUTOPILOTONE_BOARD_HPP_ */
