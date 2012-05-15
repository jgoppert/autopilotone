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

#include "interfaces.hpp"
#include "os/os.hpp"

namespace apo
{

class Navigator : public NavigatorInterface
{
// methods
public:
    Navigator () {};
    virtual ~Navigator() {};

protected:
    // reader
    virtual float get(navState_t navState) {
        m_mutex.lock();
        float val = m_state[navState];
        m_mutex.unlock();
        return val;
    }    
    virtual int32_t get(navInt32State_t navState) {
        m_mutex.lock();
        int32_t val = m_stateInt32[navState];
        m_mutex.unlock();
        return val;
    }    
    virtual int16_t get(navInt16State_t navState) {
        m_mutex.lock();
        int16_t val = m_stateInt16[navState];
        m_mutex.unlock();
        return val;
    } 

    // writer
    virtual void set(navState_t navState, float val) {
        m_mutex.lock();
        m_state[navState] = val;
        m_mutex.unlock();
    };    
    virtual void set(navInt32State_t navState, int32_t val) {
        m_mutex.lock();
        m_stateInt32[navState] = val;
        m_mutex.unlock();
    };    
    virtual void set(navInt16State_t navState, int16_t val) {
        m_mutex.lock();
        m_stateInt16[navState] = val;
        m_mutex.unlock();
    };    

    // component
    virtual void update() {};
    virtual void setDebug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * getDebug() { return m_debug; }

private:
    // attributes
    float m_state[NAV_COUNT]; 
    int16_t m_stateInt16[NAV_INT16_COUNT]; 
    int32_t m_stateInt32[NAV_INT32_COUNT]; 
    Mutex m_mutex;
    
    // interfaces
    DebugInterface * m_debug;
};

}; // namespace apo

#endif /* NAVIGATOR_HPP_ */

