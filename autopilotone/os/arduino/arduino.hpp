#ifndef AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
#define AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_

#include "../../interfaces.hpp"
#include "Arduino.h"
#include <util/atomic.h>

namespace autopilotone {

// no need for mutex on arduino, single threaded
class Mutex: public MutexInterface {
public:
    Mutex() {
        //lockFlag = false;
    }
	void lock() {
        //lockFlag = true;

        /*
        bool test = false;
        while(!test) {
            ATOMIC_BLOCK(ATOMIC_FORCEON)
            {
                test = lockFlag;
                lockFlag = true;
            }
            // delay
         }
         */
	}
	void unlock() {
        //lockFlag = false;
	}

private:
    //bool lockFlag;    
};

class Debug: public DebugInterface {
public:
	void write(const char * buf, uint32_t bytes) {
		ScopedLock lock(m_mutex);
        for (int i=0;i<bytes;i++) {
            Serial.print(buf[i]);
        }
	}
    void writeString(const char * buf) {
		ScopedLock lock(m_mutex);
        Serial.print(buf);
	}
private:
	Mutex m_mutex;
};

class Clock: public ClockInterface {
public:
	Clock() {
	}
	void sleepMicros(uint64_t micros) {
        // TODO need to implement task scheduling
        //delayMicros(micros);
	}
	uint64_t get_micros() {
        return 0;
	}
};

class SerialPort : public SerialPortInterface {
    bool available() {
        return false;
    }
    uint8_t read() {
        return 0;
    }
	void write(const char * c, uint32_t bytes) {
    }
    void writeString(const char * c) {
    }
    void update() {
    }
};

class Thread  {
public:
    void start() {
    }
    void join() {
    }
};

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
