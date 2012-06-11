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

///
// These macros define locking access for a member.
#define LOCKED_ATTR(Type,Name) \
Mutex m_lock_##Name; \
Type m_##Name;

#define LOCKED_SET(Type,Name) \
void set_##Name(Type val) { \
    m_lock_##Name.lock(); \
    m_##Name = val; \
    m_lock_##Name.unlock(); \
}

#define LOCKED_GET(Type,Name) \
Type get_##Name() { \
    m_lock_##Name.lock(); \
    Type val = m_##Name; \
    m_lock_##Name.unlock(); \
    return (val); \
}

#define LOCKED_GET_SET(Type,Name) \
LOCKED_GET(Type,Name) \
LOCKED_SET(Type,Name)

#define INT2FLOAT_GET(Name,IntName,Scale) \
float get_##Name() { \
    float val = get_##IntName()*Scale; \
    return (val); \
}

#define INT2FLOAT_SET(Name,IntName,Scale) \
void set_##Name(float val) { \
    set_##IntName(val/Scale); \
}

#define INT2FLOAT_GET_SET(Name,IntName,Scale) \
INT2FLOAT_GET(Name,IntName,Scale) \
INT2FLOAT_SET(Name,IntName,Scale)

#define LOCKED_FLAG(Name) \
LOCKED_ATTR(bool,Name)

#define LOCKED_TEST_AND_SET(Name) \
bool testAndSet_##Name() { \
    bool testVal; \
    m_lock_##Name.lock(); \
    testVal = m_##Name;\
    m_##Name = true;\
    m_lock_##Name.unlock(); \
    return (testVal); \
}

#define LOCKED_CLEAR(Name) \
bool clear_##Name() { \
    m_lock_##Name.lock(); \
    m_##Name = false; \
    m_lock_##Name.unlock(); \
}


// TODO: Add a sleep to this code
#define BLOCKING_TEST_AND_SET(Name, SleepTime) \
bool blockingTestAndSet_##Name() { \
    while (!testAndSet_##Name()) { \
        ;\
    } \
}

#define COMPLETE_TEST_AND_SET(Name, SleepTime) \
LOCKED_TEST_AND_SET(Name) \
BLOCKING_TEST_AND_SET(Name, SleepTime) \
LOCKED_CLEAR(Name)

}; // namespace autopilotone



#endif /* AUTOPILOTONE_MACROS_HPP_ */
