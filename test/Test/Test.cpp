#include "Test.ino"

int main (int argc, char const* argv[])
{
    setup();
    for(;;) {
        loop();
    }
    return(0);
}
