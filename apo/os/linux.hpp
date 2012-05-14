#include <boost/thread/mutex.hpp>

class Mutex : public MutexInterface {
public:
    Mutex() : m_mutex() {
    }
    ~Mutex() {
    }
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
