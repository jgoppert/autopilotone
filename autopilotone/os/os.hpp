#ifndef AUTOPILOTONE_OS_HPP_
#define AUTOPILOTONE_OS_HPP_

#ifndef OS
#error must define OS
#endif

#if OS == PC
#include "pc.hpp"
#else
#error must unknown OS
#endif

#endif // AUTOPILOTONE_OS_HPP_
