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

#include "interfaces.hpp"
#include "os/os.hpp"
#include "apoMacros.hpp"

namespace apo
{

class Navigator : public NavigatorInterface
{
// methods
public:
    Navigator () {};
    virtual ~Navigator() {};

    LOCKED_ATTR(int32_t,lat_degE7);
    LOCKED_ATTR(int32_t,lon_degE7);
    LOCKED_ATTR(int16_t,alt_degE3);
    LOCKED_ATTR(float,lat);
    LOCKED_ATTR(float,lon);
    LOCKED_ATTR(float,alt);
    LOCKED_ATTR(float,vNorth);
    LOCKED_ATTR(float,vEast);
    LOCKED_ATTR(float,vDown);
    LOCKED_ATTR(float,roll);
    LOCKED_ATTR(float,pitch);
    LOCKED_ATTR(float,yaw);
    LOCKED_ATTR(float,rollRate);
    LOCKED_ATTR(float,pitchRate);
    LOCKED_ATTR(float,yawRate);

protected:
    // component
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }

    // interfaces
    DebugInterface * m_debug;
};

}; // namespace apo

#endif /* NAVIGATOR_HPP_ */

