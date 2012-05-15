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
#define DEFINE_USER(Type) \
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

DEFINE_USER(Navigator);
DEFINE_USER(Guide);
DEFINE_USER(Controller);
DEFINE_USER(ParameterTable);
DEFINE_USER(Board);

///
// These macros define locking access for a member.
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

#define LOCKED_ATTR_GET_SET(Type,Name,VarAccess,GetAccess,SetAccess) \
VarAccess: \
    DEFINE_LOCKING_VAR(Type,Name); \
GetAccess: \
    DEFINE_LOCKING_GET(Type,Name); \
SetAccess: \
    DEFINE_LOCKING_SET(Type,Name); \
public:

#define LOCKED_ATTR(Type,Name) LOCKED_ATTR_GET_SET(Type,Name,private,public,protected) 

#define INT2FLOAT_ACCESS(Name,IntName,Scale) \
public: \
float CONCAT(get_,Name)() { \
    float val = CONCAT(get_,IntName)()*Scale; \
    return val; \
} \
protected: \
void CONCAT(set_,Name)(float val) { \
    CONCAT(set_,IntName)(val/Scale); \
} \
public:

}; // namespace apo



#endif /* APO_MACROS_HPP_ */


