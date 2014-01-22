//  ATMega16 LED
//
//  (C) 2009 Radu Motisan , radu.motisan@gmail.com
//  www.pocketmagic.net
//  All rights reserved.
//
//  led.c : Definitions for simple LED usage

#include "led.h"

//--------------------------------------------------------------------------------------------
void ledOn(void) {
    LED_ON(1);
}

void ledOff(void) {
    LED_OFF(1);
}

void ledToggle(void) {
    LED_TOGGLE(1);
}

