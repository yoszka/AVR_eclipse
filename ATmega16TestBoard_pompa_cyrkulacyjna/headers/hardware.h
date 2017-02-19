#ifndef INCLUDE_HARDWARE
#define INCLUDE_HARDWARE

#include <avr/io.h>

// ATmega16 board
// ****************** LED ******************************************************************
#define LED_1_PORT          PORTA
#define LED_1_DDR           DDRA
#define LED_1_BIT           0

#define LED_2_PORT          PORTA
#define LED_2_DDR           DDRA
#define LED_2_BIT           1

// ****************** SWITCH ***************************************************************
#define SWITCH_1_PORT       PORTD
#define SWITCH_1_DDR        DDRD
#define SWITCH_1_PIN        PIND
#define SWITCH_1_BIT        4

#define SWITCH_2_PORT       PORTD
#define SWITCH_2_DDR        DDRD
#define SWITCH_2_PIN        PIND
#define SWITCH_2_BIT        6

// Static macros
#define LED_1_ON            {LED_1_DDR |=  _BV(LED_1_BIT);  LED_1_PORT &= ~_BV(LED_1_BIT);}                 // NEGATIVE POLARISATION
#define LED_1_OFF           {LED_1_DDR &= ~_BV(LED_1_BIT);  LED_1_PORT |=  _BV(LED_1_BIT);}                 // NEGATIVE POLARISATION
#define LED_1_TOGGLE        {LED_1_DDR |=  _BV(LED_1_BIT);  LED_1_PORT ^=  _BV(LED_1_BIT);}                 // N/A

#define LED_2_ON            {LED_2_DDR |=  _BV(LED_2_BIT);  LED_2_PORT &= ~_BV(LED_2_BIT);}                 // NEGATIVE POLARISATION
#define LED_2_OFF           {LED_2_DDR &= ~_BV(LED_2_BIT);  LED_2_PORT |=  _BV(LED_2_BIT);}                 // NEGATIVE POLARISATION
#define LED_2_TOGGLE        {LED_2_DDR |=  _BV(LED_2_BIT);  LED_2_PORT ^=  _BV(LED_2_BIT);}                 // N/A

// Generic macros - Put the number of the led as parameter
#define LED_ON(n)           {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT &= ~_BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_OFF(n)          {LED_##n##_DDR &= ~_BV(LED_##n##_BIT);  LED_##n##_PORT |=  _BV(LED_##n##_BIT);}  // NEGATIVE POLARISATION
#define LED_TOGGLE(n)       {LED_##n##_DDR |=  _BV(LED_##n##_BIT);  LED_##n##_PORT ^=  _BV(LED_##n##_BIT);}  // N/A

#define WAIT_FOR_SWITCH_1   {SWITCH_1_DDR &= ~_BV(SWITCH_1_BIT);  SWITCH_1_PORT |= _BV(SWITCH_1_BIT); while(bit_is_set(SWITCH_1_PIN, SWITCH_1_BIT));}     // N/A

/**
 * Put the number of the switch as parameter
 */
#define CONFIG_SWITCH(n)    {SWITCH_##n##_DDR &= ~_BV(SWITCH_##n##_BIT);  SWITCH_##n##_PORT |= _BV(SWITCH_##n##_BIT);}     // N/A, Use this at beginning of program
#define WAIT_FOR_SWITCH(n)  {while(bit_is_set(SWITCH_##n##_PIN, SWITCH_##n##_BIT));}                                       // N/A

// Dead end following macros work not very well, HW is configured to slow to read its state right after.
//#define WAIT_FOR_SWITCH(n)  {SWITCH_##n##_DDR &= ~_BV(SWITCH_##n##_BIT);  SWITCH_##n##_PORT |= _BV(SWITCH_##n##_BIT); while(SWITCH_##n##_PIN & _BV(SWITCH_##n##_BIT));}     // N/A
//#define WAIT_FOR_SWITCH(n)  {SWITCH_##n##_DDR &= ~_BV(SWITCH_##n##_BIT);  SWITCH_##n##_PORT |= _BV(SWITCH_##n##_BIT); while(bit_is_set(SWITCH_##n##_PIN, SWITCH_##n##_BIT));}     // N/A

// ****************** BUZER ****************************************************************
#define BUZZER_1_PORT          PORTD
#define BUZZER_1_DDR           DDRD
#define BUZZER_1_BIT           0

#define BUZZER_2_PORT          PORTD
#define BUZZER_2_DDR           DDRD
#define BUZZER_2_BIT           1

#define BUZZ_ON(n)           {BUZZER_##n##_DDR |=  _BV(BUZZER_##n##_BIT);  BUZZER_##n##_PORT &= ~_BV(BUZZER_##n##_BIT);}
#define BUZZ_OFF(n)          {BUZZER_##n##_DDR &= ~_BV(BUZZER_##n##_BIT);  BUZZER_##n##_PORT |=  _BV(BUZZER_##n##_BIT);}

#endif // INCLUDE_HARDWARE

