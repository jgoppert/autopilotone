#include "Arduino.h"
//#include <avr-thread.h>

volatile int i = 0;

ISR(TIMER1_OVF_vect) {
    TCNT1=0xFDF8; 
}


ISR(TIMER3_OVF_vect) {
    TCNT3=0xF9C0; // Initialize timer overflow reg to give 100 us interrupts
    i++;
}


void setup()
{
    // Set up Timer1 Interrupts (Task timer)
    TIMSK1=0x01; // enabled global and timer overflow interrupt;
    TCCR1A = 0x00; // normal operation page 148 (mode0);
    TCNT1=0xFDF8; // Initialize timer overflow reg to give 10 ms interrupts
    TCCR1B = 0x04; // Prescale clock to system/256 (at 16 MHz = 62.5 kHz)

    // Set up Timer3 Interrupts (Task switching)
    TIMSK3=0x01; // enabled global and timer overflow interrupt;
    TCCR3A = 0x00; // normal operation page 148 (mode0);
    TCNT3=0xF9C0; // Initialize timer overflow reg to give 100 us interrupts
    TCCR3B = 0x01; // No clock prescale (16 MHz)

    Serial.begin(9600);
}
    
void loop()
{
    Serial.print("Begin\n");
    for(;;) {
        if(i > 10000) {
            i = 0;
            Serial.print("1 second\n");
        }
    }
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
