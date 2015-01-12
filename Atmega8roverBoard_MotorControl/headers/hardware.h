#ifndef INCLUDE_HARDWARE
#define INCLUDE_HARDWARE

#include <avr/io.h>

// ATmega8 rover board
// ****************** LED ******************************************************************

#define LED_PORT            PORTD
#define LED_DDR             DDRD
#define LED_PIN             2

// motor 1 direction
#define MOTOR_1_DIR_PORT    PORTC
#define MOTOR_1_DIR_DDR     DDRC
#define MOTOR_1_DIR_PIN     1

// motor 2 direction
#define MOTOR_2_DIR_PORT    PORTC
#define MOTOR_2_DIR_DDR     DDRC
#define MOTOR_2_DIR_PIN     0

// motor 1 enable (PWM)
#define MOTOR_1_ENA_PORT    PORTC
#define MOTOR_1_ENA_DDR     DDRC
#define MOTOR_1_ENA_PIN     2

// motor 2 enable (PWM)
#define MOTOR_2_ENA_PORT    PORTC
#define MOTOR_2_ENA_DDR     DDRC
#define MOTOR_2_ENA_PIN     3


#define LED_ON              {LED_DDR |=  _BV(LED_PIN);  LED_PORT &= ~_BV(LED_PIN);}     // NEGATIVE POLARISATION
#define LED_OFF             {LED_DDR &= ~_BV(LED_PIN);  LED_PORT |=  _BV(LED_PIN);}     // NEGATIVE POLARISATION
#define LED_TOGGLE          {LED_DDR |=  _BV(LED_PIN);  LED_PORT ^=  _BV(LED_PIN);}

#define MOTOR_1_DIR_LEFT    {MOTOR_1_DIR_DDR |=  _BV(MOTOR_1_DIR_PIN);  MOTOR_1_DIR_PORT &= ~_BV(MOTOR_1_DIR_PIN);}
#define MOTOR_1_DIR_RIGHT   {MOTOR_1_DIR_DDR |=  _BV(MOTOR_1_DIR_PIN);  MOTOR_1_DIR_PORT |=  _BV(MOTOR_1_DIR_PIN);}

#define MOTOR_2_DIR_LEFT    {MOTOR_2_DIR_DDR |=  _BV(MOTOR_2_DIR_PIN);  MOTOR_2_DIR_PORT &= ~_BV(MOTOR_2_DIR_PIN);}
#define MOTOR_2_DIR_RIGHT   {MOTOR_2_DIR_DDR |=  _BV(MOTOR_2_DIR_PIN);  MOTOR_2_DIR_PORT |=  _BV(MOTOR_2_DIR_PIN);}

#define MOTOR_1_ENA_HI      {MOTOR_1_ENA_DDR |=  _BV(MOTOR_1_ENA_PIN);  MOTOR_1_ENA_PORT |=  _BV(MOTOR_1_ENA_PIN);}
#define MOTOR_1_ENA_LOW     {MOTOR_1_ENA_DDR |=  _BV(MOTOR_1_ENA_PIN);  MOTOR_1_ENA_PORT &= ~_BV(MOTOR_1_ENA_PIN);}

#define MOTOR_2_ENA_HI      {MOTOR_2_ENA_DDR |=  _BV(MOTOR_2_ENA_PIN);  MOTOR_2_ENA_PORT |=  _BV(MOTOR_2_ENA_PIN);}
#define MOTOR_2_ENA_LOW     {MOTOR_2_ENA_DDR |=  _BV(MOTOR_2_ENA_PIN);  MOTOR_2_ENA_PORT &= ~_BV(MOTOR_2_ENA_PIN);}

#endif // INCLUDE_HARDWARE
