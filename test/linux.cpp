#include <iostream>
#include <apo/apo.hpp>
int main (int argc, char const* argv[])
{
    using namespace apo;
    Board board;
    ParameterTable parameterTable;
    Navigator navigator(&board,&parameterTable);
    Guide guide(&board,&parameterTable,&navigator);
    Controller controller(&board,&parameterTable);
    std::cout << "linux test complete" << std::endl;
    return 0;
}
