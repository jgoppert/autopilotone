#ifndef AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
#define AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_

#include "../../interfaces.hpp"
#include "Arduino.h"
#include <util/atomic.h>
#include <vector>

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
    Thread() {
    }
    void start() {
        get_threadManager().addThread(this);
    }
    void join() {
        // join does nothing, since
        // deallocating memory is discouraged
        // for arduino
    }
    virtual void run() = 0;
private:
    class ThreadManager {
    public:
        ThreadManager() {
        }
        /**
         * A simple round robin scheduling system
         */
        void run() {
            while(1) {
                for (int i=0;i<m_threads.size();i++) {
                    m_threads[i]->run();
                }
            }
        }
        void addThread(Thread * thread) {
        }
    private:
        static Vector<Thread *> m_threads;
    };
    static ThreadManager m_threadManager;
protected:
    static ThreadManager & get_threadManager() {
        return m_threadManager;
    }
};




} // namespace autopilotone

#endif // AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
