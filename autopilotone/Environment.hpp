// Environment.hpp
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Environment.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Environment.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef AUTOPILOTONE_ENVIRONMENTSIMULATION_HPP_
#define AUTOPILOTONE_ENVIRONMENTSIMULATION_HPP_

#include "interfaces.hpp"
#include "os/os.hpp"
#include "macros.hpp"

namespace autopilotone
{

class Environment : public EnvironmentInterface
{
// methods
public:
    Environment (BoardInterface * board):
        m_board(board),
        m_lat_degE7(0),
        m_lon_degE7(0),
        m_alt_degE3(0),
        m_vNorth(0),
        m_vEast(0),
        m_vDown(0),
        m_roll(0),
        m_pitch(0),
        m_yaw(0),
        m_rollRate(0),
        m_pitchRate(0),
        m_yawRate(0)
    {};
    virtual ~Environment() {};

protected:
    BoardInterface * get_board() {
        return(m_board);
    }
    LOCKED_GET_SET(int32_t,lat_degE7);
    INT2FLOAT_GET_SET(lat,lat_degE7,1.0e7*deg2rad);
    LOCKED_GET_SET(int32_t,lon_degE7);
    INT2FLOAT_GET_SET(lon,lon_degE7,1.0e7*deg2rad);
    LOCKED_GET_SET(int16_t,alt_degE3);
    INT2FLOAT_GET_SET(alt,alt_degE3,1.0e3*deg2rad);
    LOCKED_GET_SET(float,vNorth);
    LOCKED_GET_SET(float,vEast);
    LOCKED_GET_SET(float,vDown);
    LOCKED_GET_SET(float,roll);
    LOCKED_GET_SET(float,pitch);
    LOCKED_GET_SET(float,yaw);
    LOCKED_GET_SET(float,rollRate);
    LOCKED_GET_SET(float,pitchRate);
    LOCKED_GET_SET(float,yawRate);

private:
    BoardInterface * m_board;
    LOCKED_ATTR(int32_t,lat_degE7);
    LOCKED_ATTR(int32_t,lon_degE7);
    LOCKED_ATTR(int16_t,alt_degE3);
    LOCKED_ATTR(float,vNorth);
    LOCKED_ATTR(float,vEast);
    LOCKED_ATTR(float,vDown);
    LOCKED_ATTR(float,roll);
    LOCKED_ATTR(float,pitch);
    LOCKED_ATTR(float,yaw);
    LOCKED_ATTR(float,rollRate);
    LOCKED_ATTR(float,pitchRate);
    LOCKED_ATTR(float,yawRate);
};



}; // namespace autopilotone

#endif /* AUTOPILOTONE_ENVIRONMENTSIMULATION_HPP_ */

