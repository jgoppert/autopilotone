// Controller.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// Controller.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Controller.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "apoMacros.hpp"

namespace apo
{

class Controller: public BoardUser, ParameterTableUser
{

// methods
    public:
        Controller (Board * board, ParameterTable * parameterTable) : 
            BoardUser(board), 
            ParameterTableUser(parameterTable) {};
        virtual ~Controller() {};

}; // class Controller

    
}; // namespace apo


#endif /* CONTROLLER_HPP_ */
