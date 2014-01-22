#pragma once
/*
 * Arduino UNO board
 *
 * (C) 2014 Tomasz Jokiel , tomasz.jokiel@gmail.com
 *
 * LED.h: Definitions for LED usage
 */
#include <avr/io.h>

// ****************** LED ******************************************************************
#define LED_1_PORT          PORTB   // PIN 8
#define LED_1_DDR           DDRB
#define LED_1_BIT           0

// Generic macros - Put the number of the led as parameter
#define LED_ON(n)           {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT &= ~_BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_OFF(n)          {LED_##n##_DDR &= ~_BV(LED_##n##_BIT);  LED_##n##_PORT |=  _BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_TOGGLE(n)       {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT ^=  _BV(LED_##n##_BIT);}  // N/A

// Function definition
void ledOn(void);
void ledOff(void);
void ledToggle(void);
