#ifndef APO_OS_HPP_
#define APO_OS_HPP_

#ifndef OS
#error must define OS
#endif

class MutexInterface {
public:
    virtual bool try_lock() = 0;
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

#if OS == LINUX
#include "linux.hpp"
#else
#error must unknown OS
#endif

#endif // APO_OS_HPP_
