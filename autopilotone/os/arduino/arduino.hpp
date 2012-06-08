#include "../../interfaces.hpp"

class Mutex : public MutexInterface {
public:
    void lock() { m_lock = true; }
    void unlock() { m_lock = false; }
private:
    bool m_lock;
};
