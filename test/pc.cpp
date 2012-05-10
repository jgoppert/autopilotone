#include <iostream>
#include <apo/apo.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

namespace apo {

class TestNavigator : public Navigator {
public:
    TestNavigator(Board * board, ParameterTable * parameterTable) : Navigator(board,parameterTable) {}
    bool update() {
        return set_lat(1) && set_lon(1) && set_alt(1);
    }
};

void navReader(int id, apo::TestNavigator * navigator,uint32_t  * failureCount, 
        uint32_t totalCycles, uint32_t sleepmillis) {
    uint32_t lat = 0;
    for (int i=0;i<totalCycles;i++) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        while(!navigator->get_lat(lat)) {
            (*failureCount)++;
            boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        }
    }
}

void navWriter(int id, apo::TestNavigator * navigator,uint32_t  * failureCount,
        uint32_t totalCycles, uint32_t sleepmillis) {
    for (int i=0;i<totalCycles;i++) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        while(!navigator->update()) {
            (*failureCount)++;
            boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        }
    }
}

}

int main (int argc, char const* argv[])
{
    using namespace apo;
    Board board;
    ParameterTable parameterTable;
    TestNavigator navigator(&board,&parameterTable);

    // settings // sleep currently disabled, if enabled, no read/write failures occur
    uint32_t sleepmillis1 = 0;
    uint32_t sleepmillis2 = 0;
    uint32_t sleepmillis3 = 0;
    uint32_t totalCycles = 100000;

    // data
    uint32_t failureCount1 = 0;
    uint32_t failureCount2 = 0;
    uint32_t failureCount3 = 0;

    // threads
    boost::thread thread1(navReader,1,&navigator,&failureCount1,totalCycles,sleepmillis1);
    boost::thread thread2(navReader,2,&navigator,&failureCount2,totalCycles,sleepmillis2);
    boost::thread thread3(navWriter,3,&navigator,&failureCount3,totalCycles,sleepmillis3);

    thread1.join();
    thread2.join();

    std::cout << "Total test cycles: # " << totalCycles << std::endl;
    std::cout << "Thread 1 read blocked: # " << failureCount1 << ", "
        << 100.0*failureCount1/totalCycles << "%" << std::endl;
    std::cout << "Thread 2 read blocked: # " << failureCount2 << ", "
        << 100.0*failureCount2/totalCycles << "%" << std::endl;
    std::cout << "Thread 3 write blocked: # " << failureCount3 << ", "
        << 100.0*failureCount3/totalCycles << "%" << std::endl;
    return 0;
}
