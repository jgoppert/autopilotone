// FlightPlan.cpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// FlightPlan.cpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FlightPlan.cpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "FlightPlan.hpp"

namespace apo
{
    // read interface
    uint16_t FlightPlan::get_currentCommandIndex()
    {
        return m_commandIndex;
    }



}; // namespace apo

