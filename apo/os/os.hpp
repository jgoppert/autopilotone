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
