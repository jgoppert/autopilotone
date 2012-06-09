#include "Arduino.h"

int i = 0;

ISR(TIMER1_OVF_vect) {
    TCNT1=0x0BDC;
    i++;  
}

void setup()
{
    TIMSK1=0x01; // enabled global and timer overflow interrupt;
    TCCR1A = 0x00; // normal operation page 148 (mode0);
    TCNT1=0x0BDC; // set initial value to remove time error (16bit counter register)
    TCCR1B = 0x04; //

    Serial.begin(9600);
}
    
void loop()
{
    Serial.print(i);
}
/*
int main (int argc, char const* argv[])
{
    Serial3.begin(9600);

    for(;;) {
        Serial3.write("test\n");
    }
    
        return 0;
}
*/
