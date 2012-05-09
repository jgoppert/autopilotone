// TypeUser.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// TypeUser.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// TypeUser.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TYPE_USER_HPP_
#define TYPE_USER_HPP_

namespace apo {

///
// This file contains a macro to define a user of a class with
// an accessor with protected access.
#define DEFINE_TYPE_USER(Type,TypeUser)              \
class Type;                                          \
class TypeUser {                                     \
public:                                              \
    TypeUser(Type * TypeVal) : m_Type(TypeVal) {};   \
    virtual ~TypeUser() {};                          \
private:                                             \
    Type * m_Type;                                   \
protected:                                           \
    virtual Type * getType() { return m_Type; }      \
                                                     \
};

DEFINE_TYPE_USER(Navigator,NavigatorUser);
DEFINE_TYPE_USER(Guide,GuideUser);
DEFINE_TYPE_USER(Controller,ControllerUser);
DEFINE_TYPE_USER(ParameterTable,ParameterTableUser);
DEFINE_TYPE_USER(Board,BoardUser);

}; // namespace apo

#endif /* TYPE_USER_HPP_ */


