#ifndef APO_OS_LINUX_HPP_
#define APO_OS_LINUX_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>
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

class Clock : public ClockInterface {
public:
    Clock() : m_startTime(boost::posix_time::microsec_clock::universal_time()) {
    }
    void sleepMicros(uint64_t micros) {
        boost::this_thread::sleep(boost::posix_time::microseconds(micros)); 
    }
    uint64_t get_micros() {
        boost::posix_time::time_duration elapsed =
            boost::posix_time::microsec_clock::universal_time() - get_startTime();
        return elapsed.total_microseconds();
    }
protected:
    boost::posix_time::ptime  get_startTime() { return m_startTime; }
private:
    boost::posix_time::ptime m_startTime;       
}clock;


} // namespace apo

#endif // APO_OS_LINUX_HPP_
