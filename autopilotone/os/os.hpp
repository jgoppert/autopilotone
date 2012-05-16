#ifndef APO_OS_HPP_
#define APO_OS_HPP_

#ifndef OS
#error must define OS
#endif

#if OS == PC
#include "pc.hpp"
#else
#error must unknown OS
#endif

#endif // APO_OS_HPP_
