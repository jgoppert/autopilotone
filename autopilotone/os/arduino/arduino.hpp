#ifndef AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
#define AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_

#include "../../interfaces.hpp"
#include "Arduino.h"
#include <util/atomic.h>
#include <vector>
#include <pt.h>

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
    Debug() {
        Serial.begin(115200);
    }
    void write(const char * buf, uint32_t bytes) {
        ScopedLock lock(m_mutex);
        for (int i=0; i<bytes; i++) {
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
        delayMicroseconds(micros);
    }
    uint64_t get_micros() {
        return micros();
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

struct ThreadInterface_PT : public ThreadInterface, public pt {
    ThreadInterface_PT() : pt() {
    }
    virtual int pt_run() = 0;
};

class Scheduler {
public:
    /**
     * A simple round robin scheduling system
     */
    int run() {
        for (int i=0; i<m_threads.size(); i++) {
            m_threads[i]->pt_run();
        }
    }
    void addThread(ThreadInterface_PT * thread) {
        m_threads.push_back(thread);
    }
private:
    Vector<ThreadInterface_PT *> m_threads;
} scheduler;


class TimerThread : public ThreadInterface_PT {
public:
    TimerThread(float frequency, ProcessInterface * process, ClockInterface * clock) :
        m_periodMicros(1000000.0/frequency), m_running(false),
        m_start(), m_timestamp(),
        m_process(process), m_clock(clock) {
        PT_INIT(this);
        start();
    }
    void start() {
        scheduler.addThread(this);
    }
    void join() {
    }
    int pt_run() {
        PT_BEGIN(this);
        while(1) {
            PT_WAIT_UNTIL(this, get_clock()->get_micros() - m_timestamp > m_periodMicros );
            m_timestamp = get_clock()->get_micros();
            get_process()->update();
        }
        PT_END(this);
    }
protected:
    LOCKED_GET_SET(bool,running);
    ProcessInterface * get_process() {
        return m_process;
    }
    ClockInterface * get_clock() {
        return m_clock;
    }
    uint64_t get_periodMicros() {
        return m_periodMicros;
    }
private:
    uint64_t m_periodMicros;
    LOCKED_ATTR(volatile bool,running);
    uint64_t m_start;
    uint32_t m_timestamp;
    ProcessInterface * m_process;
    ClockInterface * m_clock;
};


} // namespace autopilotone

#endif // AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
