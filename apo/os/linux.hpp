#ifndef APO_OS_LINUX_HPP_
#define APO_OS_LINUX_HPP_

#include <boost/thread/mutex.hpp>
#include <iostream>
#include "../interfaces.hpp"

namespace apo {

class Mutex : public MutexInterface {
public:
    void lock() {
        return m_mutex.lock();
    }
    bool try_lock() {
        return m_mutex.try_lock();
    }
    void unlock() {
        return m_mutex.unlock();
    }
private:
    boost::mutex m_mutex;
};

class Debug : public DebugInterface {
public:
    void send(const std::string & str) {
        m_mutex.lock();
        std::cout << str << std::endl;
        m_mutex.unlock();
    }
private:
    Mutex m_mutex;
};

} // namespace apo

#endif // APO_OS_LINUX_HPP_
