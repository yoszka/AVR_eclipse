#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "headers/hardware.h"

#if defined (__AVR_ATmega8__)
    #define MOSI_PIN    3
    #define MISO_PIN    4
    #define SCK_PIN     5
    #define SS_PIN      2
#elif
    #error "Not ATmega8"
#endif

void configureSpiMaster()
{
    DDRB  |= _BV(MOSI_PIN) | _BV(SCK_PIN) | _BV(SS_PIN);
    PORTB |= _BV(SS_PIN);
    SPCR  |= _BV(SPE) | _BV(MSTR) | _BV(SPI2X);
}

uint8_t sendReceiveSpiByte(uint8_t value)
{
    PORTB &= ~_BV(SS_PIN);
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    PORTB |= _BV(SS_PIN);
    SPSR  |= _BV(SPIF);
    PORTB |= _BV(SS_PIN);
    return SPDR;
}

void send1Receive3Spi(uint8_t value)
{
    PORTB &= ~_BV(SS_PIN);
    _delay_us(12);

    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    SPSR |= _BV(SPIF);

    // Send dummy bytes to receive 3 byte answer
    SPDR = 0xFF;
    loop_until_bit_is_set(SPSR, SPIF);
    SPSR |= _BV(SPIF);

    SPDR = 0xFF;
    loop_until_bit_is_set(SPSR, SPIF);
    SPSR |= _BV(SPIF);

    SPDR = 0xFF;
    loop_until_bit_is_set(SPSR, SPIF);
    SPSR |= _BV(SPIF);

    PORTB |= _BV(SS_PIN);
    PORTB |= _BV(SS_PIN);
}

// ****************** DEFINITION ***********************************************************

// ****************** Global variables ******************************************************
// *****************************************************************************************

int main (void)
{

    CONFIG_SWITCH(1)

    configureSpiMaster();
    send1Receive3Spi(0x9F);

    while(true)
    {
        LED_1_ON
        _delay_ms(1000);
        WAIT_FOR_SWITCH(1)
        _delay_ms(100);
        LED_1_OFF
        _delay_ms(100);

        send1Receive3Spi(0x9F);
    }
}

//******************************************************************************
//******************************************************************************

