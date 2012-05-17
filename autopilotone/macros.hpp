// macros.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// macros.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// macros.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef AUTOPILOTONE_MACROS_HPP_
#define AUTOPILOTONE_MACROS_HPP_

#include <inttypes.h>

namespace autopilotone {

#define CONCAT_HELPER(X,Y) X##Y
#define CONCAT(X,Y) CONCAT_HELPER(X,Y)

///
// These macros define locking access for a member.
#define LOCKED_ATTR(Type,Name) \
Mutex CONCAT(m_lock_,Name); \
Type CONCAT(m_,Name);

#define LOCKED_SET(Type,Name) \
void CONCAT(set_,Name)(Type val) { \
    CONCAT(m_lock_,Name).lock(); \
    CONCAT(m_,Name) = val; \
    CONCAT(m_lock_,Name).unlock(); \
}

#define LOCKED_GET(Type,Name) \
Type CONCAT(get_,Name)() { \
    CONCAT(m_lock_,Name).lock(); \
    Type val = CONCAT(m_,Name); \
    CONCAT(m_lock_,Name).unlock(); \
    return val; \
}

#define LOCKED_GET_SET(Type,Name) \
LOCKED_GET(Type,Name) \
LOCKED_SET(Type,Name)

#define INT2FLOAT_GET(Name,IntName,Scale) \
float CONCAT(get_,Name)() { \
    float val = CONCAT(get_,IntName)()*Scale; \
    return val; \
}

#define INT2FLOAT_SET(Name,IntName,Scale) \
void CONCAT(set_,Name)(float val) { \
    CONCAT(set_,IntName)(val/Scale); \
}

#define INT2FLOAT_GET_SET(Name,IntName,Scale) \
INT2FLOAT_GET(Name,IntName,Scale) \
INT2FLOAT_SET(Name,IntName,Scale)

#define LOCKED_FLAG(Name) \
LOCKED_ATTR(bool,Name)
    
#define BLOCKING_TEST_AND_SET(Name, SleepTime) \
LOCKED_GET_SET(bool, Name) \
bool CONCAT(blockingTestAndSet_,Name)() { \
    while (!CONCAT(get_,Name)() { \
        \\sleep(SleepTime); \
    } \
}



}; // namespace autopilotone



#endif /* AUTOPILOTONE_MACROS_HPP_ */
