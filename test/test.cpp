
#include <util/atomic.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main (int argc, char const* argv[])
{

    TCCR2 = _BV(WGM21) | _BV(CS21) | _BV(CS20);
    OCR2 = 62;
    TCNT2 = 0;
    TIMSK |= _BV(OCIE2);

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
            for(;;){}
    }
};

