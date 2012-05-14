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

#include "os/os.hpp"
#include <inttypes.h>

namespace apo {

#define CONCAT_HELPER(X,Y) X##Y
#define CONCAT(X,Y) CONCAT_HELPER(X,Y)

///
// This macro defines a user of a class with
// an accessor with protected access.
#define DEFINE_APO_MACROS(Type) \
class Type; \
class CONCAT(Type,User) { \
public: \
    CONCAT(Type,User)(Type * TypeVal) : CONCAT(m_,Type)(TypeVal) {}; \
    virtual ~CONCAT(Type,User)() {}; \
private: \
    Type * CONCAT(m_,Type); \
protected: \
    virtual Type * CONCAT(get,Type)() { return CONCAT(m_,Type); } \
};

DEFINE_APO_MACROS(Navigator);
DEFINE_APO_MACROS(Guide);
DEFINE_APO_MACROS(Controller);
DEFINE_APO_MACROS(ParameterTable);
DEFINE_APO_MACROS(Board);

///
// These macros defines locking acces for a member.
// They return true if the set/get was successful, otherwise they returns false.
#define DEFINE_LOCKING_VAR(Type,Name) \
Mutex CONCAT(m_lock_,Name); \
Type CONCAT(m_,Name);

#define DEFINE_LOCKING_SET(Type,Name) \
void CONCAT(set_,Name)(Type val) { \
    CONCAT(m_lock_,Name).lock(); \
    CONCAT(m_,Name) = val; \
    CONCAT(m_lock_,Name).unlock(); \
}

#define DEFINE_LOCKING_GET(Type,Name) \
Type CONCAT(get_,Name)() { \
    CONCAT(m_lock_,Name).lock(); \
    Type val = CONCAT(m_,Name); \
    CONCAT(m_lock_,Name).unlock(); \
    return val; \
}

#define LOCKED_ATTR_PUBLIC_GET_PROTECTED_SET(Type,Name) \
private: \
    DEFINE_LOCKING_VAR(Type,Name); \
protected: \
    DEFINE_LOCKING_SET(Type,Name); \
public: \
    DEFINE_LOCKING_GET(Type,Name);

#define LOCKED_ATTR_PUBLIC_GET_PUBLIC_SET(Type,Name) \
private: \
    DEFINE_LOCKING_VAR(Type,Name); \
public: \
    DEFINE_LOCKING_GET(Type,Name); \
    DEFINE_LOCKING_SET(Type,Name);

}; // namespace apo



#endif /* APO_MACROS_HPP_ */


