/*
 * hardware.h
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef INCLUDE_HARDWARE
#define INCLUDE_HARDWARE

#include <avr/io.h>

// ATmega8 board
// ****************** LED ******************************************************************
#define LED_1_PORT          PORTB
#define LED_1_DDR           DDRB
#define LED_1_PIN           0

#define LED_2_PORT          PORTB
#define LED_2_DDR           DDRB
#define LED_2_PIN           1

#define LED_3_PORT          PORTC
#define LED_3_DDR           DDRC
#define LED_3_PIN           5

#define LED_1_ON            {LED_1_DDR |=  _BV(LED_1_PIN);  LED_1_PORT |=  _BV(LED_1_PIN);}     // POSITIVE POLARISATION
#define LED_1_OFF           {LED_1_DDR &= ~_BV(LED_1_PIN);  LED_1_PORT &= ~_BV(LED_1_PIN);}     // POSITIVE POLARISATION
#define LED_1_TOGGLE        {LED_1_DDR |=  _BV(LED_1_PIN);  LED_1_PORT ^=  _BV(LED_1_PIN);}     // POSITIVE POLARISATION

#define LED_2_ON            {LED_2_DDR |=  _BV(LED_2_PIN);  LED_2_PORT &= ~_BV(LED_2_PIN);}     // NEGATIVE POLARISATION
#define LED_2_OFF           {LED_2_DDR &= ~_BV(LED_2_PIN);  LED_2_PORT |=  _BV(LED_2_PIN);}     // NEGATIVE POLARISATION

#define LED_3_ON            {LED_3_DDR |=  _BV(LED_3_PIN);  LED_3_PORT &= ~_BV(LED_3_PIN);}     // NEGATIVE POLARISATION
#define LED_3_OFF           {LED_3_DDR &= ~_BV(LED_3_PIN);  LED_3_PORT |=  _BV(LED_3_PIN);}     // NEGATIVE POLARISATION


#define SWITCH_1_PORT       PORTD
#define SWITCH_1_DDR        DDRD
#define SWITCH_1_PIN        PIND
#define SWITCH_1_BIT        3

/**
 * Put the number of the switch as parameter
 */
#define CONFIG_SWITCH(n)    {SWITCH_##n##_DDR &= ~_BV(SWITCH_##n##_BIT);  SWITCH_##n##_PORT |= _BV(SWITCH_##n##_BIT);}     // N/A, Use this at beginning of program
#define WAIT_FOR_SWITCH(n)  {while(bit_is_set(SWITCH_##n##_PIN, SWITCH_##n##_BIT));}                                       // N/A

#endif // INCLUDE_HARDWARE
