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
#define LED_1_PORT          PORTD   // PIN 6
#define LED_1_DDR           DDRD
#define LED_1_BIT           6

#define LED_2_PORT          PORTD   // PIN 5
#define LED_2_DDR           DDRD
#define LED_2_BIT           5

// Generic macros - Put the number of the led as parameter
#define LED_ON(n)           {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT &= ~_BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_OFF(n)          {LED_##n##_DDR &= ~_BV(LED_##n##_BIT);  LED_##n##_PORT |=  _BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_TOGGLE(n)       {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT ^=  _BV(LED_##n##_BIT);}  // N/A

// Function definition
void ledOn(void);
void ledOff(void);
void ledToggle(void);

void led2On(void);
void led2Off(void);
void led2Toggle(void);

// ****************** LED ******************************************************************
// S1 = PD3
// S2 = PD4
