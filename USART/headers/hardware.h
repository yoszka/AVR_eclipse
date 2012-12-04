#ifndef INCLUDE_HARDWARE
#define INCLUDE_HARDWARE

#include <avr/io.h>

// ****************** LED ******************************************************************
#define LED_1_PORT		 PORTB
#define LED_1_DDR		 DDRB
#define LED_1_PIN		 0

#define LED_2_PORT		 PORTB
#define LED_2_DDR		 DDRB
#define LED_2_PIN		 1

#define LED_3_PORT		 PORTC
#define LED_3_DDR		 DDRC
#define LED_3_PIN		 5

#define LED_1_ON		 {LED_1_DDR |=  _BV(LED_1_PIN);  LED_1_PORT |=  _BV(LED_1_PIN);}		// POSITIVE POLARISATION 
#define LED_1_OFF		 {LED_1_DDR &= ~_BV(LED_1_PIN);  LED_1_PORT &= ~_BV(LED_1_PIN);}		// POSITIVE POLARISATION
#define LED_1_TOGGLE	 {LED_1_DDR |=  _BV(LED_1_PIN);  LED_1_PORT ^=  _BV(LED_1_PIN);}		// POSITIVE POLARISATION

#define LED_2_ON		 {LED_2_DDR |=  _BV(LED_2_PIN);  LED_2_PORT &= ~_BV(LED_2_PIN);}		// NEGATIVE POLARISATION 
#define LED_2_OFF		 {LED_2_DDR &= ~_BV(LED_2_PIN);  LED_2_PORT |=  _BV(LED_2_PIN);}		// NEGATIVE POLARISATION 

#define LED_3_ON		 {LED_3_DDR |=  _BV(LED_3_PIN);  LED_3_PORT &= ~_BV(LED_3_PIN);}		// NEGATIVE POLARISATION 
#define LED_3_OFF		 {LED_3_DDR &= ~_BV(LED_3_PIN);  LED_3_PORT |=  _BV(LED_3_PIN);}		// NEGATIVE POLARISATION 

#endif // INCLUDE_HARDWARE
