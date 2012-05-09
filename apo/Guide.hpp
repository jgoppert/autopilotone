// Guide.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Guide.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Guide.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GUIDE_HPP_
#define GUIDE_HPP_

#include "TypeUser.hpp"

namespace apo
{

// forward declrations
class Navigator;
class Parameters;

class Guide: public BoardUser, ParameterTableUser, NavigatorUser {

// methods
    public:
        Guide (Board * board, ParameterTable * parameterTable, Navigator * navigator) : 
            BoardUser(board),
            ParameterTableUser(parameterTable),
            NavigatorUser(navigator) {};
        virtual ~Guide() {};

// accessors
        
}; // class Guide

}; // namespace apo


#endif /* GUIDE_HPP_ */

