#include <avr/io.h>
#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "headers/hardware.h"
#include "headers/motor.h"

#define ONE_SECOND_TIMER_VAL    31

volatile UINT uiSoftCounter = 0;

void initTimer0(void)
{
    // prescaler F_CPU/1024
    TCCR0 |= (1<<CS00) | (1<<CS02);
    // interrupt from overflow
    TIMSK |= 1<<TOIE0;
    // start value
    TCNT0 = 1;
}

void resetTimer0(void)
{
    // set timer value
    TCNT0 = 1;
    uiSoftCounter = 0;
}

ISR(TIMER0_OVF_vect)
{
    if(++uiSoftCounter == ONE_SECOND_TIMER_VAL)
    {
        uiSoftCounter = 0;
        // 1 second
        LED_2_TOGGLE

        vMotorStop();
    }
}
