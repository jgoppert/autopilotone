#ifndef AUTOPILOTONE_OS_HPP_
#define AUTOPILOTONE_OS_HPP_

#if OS_PC
#include "pc/pc.hpp"
#elif OS_ARDUINO
#include "arduino/arduino.hpp"
#endif

#endif // AUTOPILOTONE_OS_HPP_
