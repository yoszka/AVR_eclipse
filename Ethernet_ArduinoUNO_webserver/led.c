/**
 * led.c
 *
 * (C) 2014 Tomasz Jokiel , tomasz.jokiel@gmail.com
 */

#include "led.h"

void led1On(void) {
    LED_ON(1);
}

void led1Off(void) {
    LED_OFF(1);
}

void led1Toggle(void) {
    LED_TOGGLE(1);
}

void led2On(void) {
    LED_ON(2);
}

void led2Off(void) {
    LED_OFF(2);
}

void led2Toggle(void) {
    LED_TOGGLE(2);
}

