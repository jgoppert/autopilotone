#ifndef AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
#define AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_

#include "../../interfaces.hpp"
#include "Arduino.h"
#include <vector>
#include "../generic/protothreads.hpp"

namespace autopilotone {

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

} // namespace autopilotone

#endif // AUTOPILOTONE_OS_ARDUINO_ARDUINO_HPP_
