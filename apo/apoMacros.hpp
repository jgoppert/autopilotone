// apoMacros.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// apoMacros.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// apoMacros.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef APO_MACROS_HPP_
#define APO_MACROS_HPP_

#include <inttypes.h>

namespace apo {

#define CONCATENATE_HELPER(X,Y) X##Y
#define CONCATENATE(X,Y) CONCATENATE_HELPER(X,Y)

///
// This macro defines a user of a class with
// an accessor with protected access.
#define DEFINE_APO_MACROS(Type)                                                 \
class Type;                                                                    \
class CONCATENATE(Type,User) {                                                 \
public:                                                                        \
    CONCATENATE(Type,User)(Type * TypeVal) : CONCATENATE(m_,Type)(TypeVal) {}; \
    virtual ~CONCATENATE(Type,User)() {};                                      \
private:                                                                       \
    Type * CONCATENATE(m_,Type);                                               \
protected:                                                                     \
    virtual Type * CONCATENATE(get,Type)() { return CONCATENATE(m_,Type); }    \
};

DEFINE_APO_MACROS(Navigator);
DEFINE_APO_MACROS(Guide);
DEFINE_APO_MACROS(Controller);
DEFINE_APO_MACROS(ParameterTable);
DEFINE_APO_MACROS(Board);

///
// These macros defines locking acces for a member.
// They return true if the set/get was successful, otherwise they returns false.
#define DEFINE_LOCKING_VAR(Type,Name)                                           \
bool CONCATENATE(m_lock_,Name);                                                 \
Type CONCATENATE(m_,Name);

#define DEFINE_LOCKING_SET(Type,Name)                                           \
bool CONCATENATE(set_,Name)(Type val) {                                         \
    if (!CONCATENATE(m_lock_,Name)) {                                           \
        CONCATENATE(m_lock_,Name) = true;                                       \
        CONCATENATE(m_,Name) = val;                                             \
        CONCATENATE(m_lock_,Name) = false;                                      \
        return true;                                                            \
    } else {                                                                    \
        return false;                                                           \
    }                                                                           \
}

#define DEFINE_LOCKING_GET(Type,Name)                                           \
bool CONCATENATE(get_,Name)(Type val) {                                         \
    if (!CONCATENATE(m_lock_,Name)) {                                           \
        CONCATENATE(m_lock_,Name) = true;                                       \
        val = CONCATENATE(m_,Name);                                             \
        CONCATENATE(m_lock_,Name) = false;                                      \
        return true;                                                            \
    } else {                                                                    \
        return false;                                                           \
    }                                                                           \
}

}; // namespace apo

#endif /* APO_MACROS_HPP_ */


