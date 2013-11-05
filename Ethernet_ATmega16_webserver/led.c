//  ATMega16 LED
//
//  (C) 2009 Radu Motisan , radu.motisan@gmail.com
//  www.pocketmagic.net
//  All rights reserved.
//
//  led.c : Definitions for simple LED usage



#include "led.h"

int led_state = 0;
int LEDInit()
{
    LED_OUTPUT_MODE();

    return 1;
}

//--------------------------------------------------------------------------------------------
// set led on off
int LEDSet(int st)	
{
    led_state = st;
    if (st)
        LED_HIGH();
    else
        LED_LOW();
    return 1;
}

void LEDToggle() {
    if (led_state) LEDSet(0); else LEDSet(1);
}
