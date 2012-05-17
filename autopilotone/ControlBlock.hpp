// ControlBlock.hpp 
// Copyright (C) James Goppert 2012 <james.goppert@gmail.com>
//
// ControlBlock.hpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ControlBlock.hpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CONTROL_BLOCK_HPP_
#define CONTROL_BLOCK_HPP_

#include "interfaces.hpp"
#include "FlightPlan.hpp"
#include <vector>

namespace autopilotone
{

class ControlBlock : public ComponentInterface {

// methods
public:
    ControlBlock (GuideReadInterface * guide) :
        m_guide(guide), m_debug(&nullDebug)
    {}; 
    virtual ~ControlBlock() {};
    
    virtual void update() {};
    virtual void set_debug(DebugInterface * debug) {m_debug = debug; }
    virtual DebugInterface * get_debug() { return m_debug; }

    // read interface

    // write interface
    virtual void set_integratorSaturation(float integerSat) {
        m_integratorSaturation = integerSat;
    }

    virtual void set_integratorBleedFactor(float bleedFactor) {
        if(bleedFactor <= 1 && bleedFactor > 0) {
            m_integratorBleedFactor = bleedFactor;
        }
    }
    
protected:
    float m_kd;
    float m_ki;
    float m_ki;

    float m_integratorSaturation;
    float m_integratorBleedFactor;

    float m_cutoffFrequency_radps;
private:
    DebugInterface * m_debug;
    GuideReadInterface * m_guide;

}; // class ControlBlock

struct BlockInterface {
    virtual float update(float input, float dt) = 0;
}

class SaturationBlock {
    public:
        static float saturate(float value, float limit) {
            if(value > limit)
            {
                value = limit;
            } else if (value < -limit) {
                value = -limit;
            }

            return value;
        }
}

class IntegratorBlock : public BlockInterface {
    public:
        IntegratorBlock(float ki, float iSat) :
            m_integratorSaturation(iSat), m_ki(ki), m_i(0)
        {};

        virtual float update(float input, float dt) {
            m_i += input * dt;
            SaturationBlock::saturate(input, m_integratorSaturation);

            return m_ki*m_i;
        }

    protected:
        float m_ki;
        float m_integratorSaturation;

    private:
        float m_i;
}

class LowPassFilterBlock : public BlockInterface {
    public:
        LowPassFilterBlock(float cutoffFrequency_radps) :
            m_RC(1/(2*M_PI*cutoffFrequency_radps)), m_output(0)
        {};

        virtual float update(float input, float dt) {
            float alpha = dt/(RC + dt);
            m_output = (1 - alpha) * m_output + alpha*input;
            return m_output;


    protected:
        float m_RC;
        float m_output;
};

class ProportionalBlock : public BlockInterface {
    public:
        ProportionalBlock(float kp) :
            m_kp(kp)
        {};

        virtual float update(float input, float dt) {
            return input*m_kp;
        }

    protected:
        float m_kp;
};

class DerivativeBlock : public BlockInterface {
    public:
        DerivativeBlock(float kd) :
            m_kd(kd), m_output(0), m_firstRun(true)
        {};

        virtual float update(float input, float dt) {
            if(m_firstRun)
            {
                m_output = 0;
                m_firstRun = false;
            }
            else
            {
                m_output = (dt > 0) ? (m_output - input)/dt : 0;
                return m_output;
            }
        }

    protected:
        float m_kd;
        float m_output;
        bool m_firstRun;
};

class PIDBlock : BlockInterface {
    public:
        PIDBlock(float kp, float ki, float kd, float cutoffFreq_radps, float iSat, float ySat) :
            m_integral(ki, iSat), m_proportional(kp), m_derivative(kd), m_filter(cutoffFreq_radps)
        {};

        virtual void update(float input, float dt) {
            float filteredError = m_filter.update(input, dt);

            float output;
            output = m_integral.update(filteredError,dt);
            output += m_derivative.update(filteredError,dt);
            output += m_proportional.update(filteredError,dt);
            output = SaturationBlock::saturate(output, ySat);

            return output;
        }

    protected:
        IntegralBlock m_integral;
        ProportionalBlock m_proportional;
        DerivativeBlock m_derivative;
        LowPassFilterBlock m_filter;
};

}; // namespace autopilotone


#endif /* GUIDE_HPP_ */

