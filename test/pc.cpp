#include <iostream>
#include <apo/apo.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

namespace apo {

class TestNavigator : public Navigator {
public:
    TestNavigator(Board * board, ParameterTable * parameterTable) : Navigator(board,parameterTable) {}
    void update() {
        set_lat(1);
        set_lon_degE7(1000);
        set_lon(1);
        set_alt(1);
    }
};

void navReader(int id, apo::TestNavigator * navigator,uint32_t totalCycles, uint32_t sleepmillis) {
    uint32_t lat = 0;
    for (int i=0;i<totalCycles;i++) {
        std::cout << "read " << i << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        lat = navigator->get_lat();
    }
}

void navWriter(int id, apo::TestNavigator * navigator,uint32_t totalCycles, uint32_t sleepmillis) {
    for (int i=0;i<totalCycles;i++) {
        std::cout << "write " << i << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleepmillis));
        navigator->update();
    }
}

}

int main (int argc, char const* argv[])
{
    using namespace apo;
    Board board;
    ParameterTable parameterTable;
    TestNavigator navigator(&board,&parameterTable);
    Guide guide(&board,&parameterTable,&navigator);
    Controller controller(&board,&parameterTable,&navigator,&guide);

    uint32_t sleepmillis1 = 1;
    uint32_t sleepmillis2 = 2;
    uint32_t sleepmillis3 = 3;
    uint32_t totalCycles = 1000;

    // threads
    boost::thread thread1(navReader,1,&navigator,totalCycles,sleepmillis1);
    boost::thread thread2(navReader,2,&navigator,totalCycles,sleepmillis2);
    boost::thread thread3(navWriter,3,&navigator,totalCycles,sleepmillis3);

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Total test cycles: # " << totalCycles << std::endl;
    return 0;
}

