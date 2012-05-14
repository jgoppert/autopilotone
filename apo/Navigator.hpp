// Navigator.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Navigator.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Navigator.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef NAVIGATOR_HPP_
#define NAVIGATOR_HPP_

#include "apoMacros.hpp"

namespace apo
{

class Navigator: public BoardUser, ParameterTableUser
{

// methods
public:
    Navigator (Board * board, ParameterTable * parameterTable) : 
        BoardUser(board),
        ParameterTableUser(parameterTable) {};
    virtual ~Navigator() {};

// attributes
public:

    /// latitude, expressed in degrees * 1E7
    LOCKED_ATTR(uint32_t,lat_degE7);
    INT2FLOAT_ACCESS(lat,lat_degE7,1.0e7*M_PI/180)

    /// longitude, expressed in degrees * 1E7
    LOCKED_ATTR(uint32_t,lon_degE7);
    INT2FLOAT_ACCESS(lon,lon_degE7,1.0e7*M_PI/180)

    /// altitude, expressed in degrees * 1E7
    LOCKED_ATTR(uint16_t,alt_degE3);
    INT2FLOAT_ACCESS(alt,alt_degE3,1.0e3*M_PI/180)

    /// north velocity, m/s
    LOCKED_ATTR(uint32_t,vN);

    /// east velocity, m/s
    LOCKED_ATTR(uint32_t,vE);

    /// down velocity, m/s
    LOCKED_ATTR(uint32_t,vD);

    /// roll, rad
    LOCKED_ATTR(float,roll);

    /// pitch, rad
    LOCKED_ATTR(float,pitch);

    /// yaw, rad
    LOCKED_ATTR(float,yaw);

    /// roll rate, rad/s
    LOCKED_ATTR(float,rollRate);

    /// pitch rate, rad/s
    LOCKED_ATTR(float,pitchRate);

    /// yaw rate, rad/s
    LOCKED_ATTR(float,yawRate);

}; // class Navigator

}; // namespace apo

#endif /* NAVIGATOR_HPP_ */

