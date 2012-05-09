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

#include "TypeUser.hpp"

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

// accessors
        
}; // class Navigator

}; // namespace apo

#endif /* NAVIGATOR_HPP_ */

