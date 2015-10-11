#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "headers/global_types.h"
#include "headers/hardware.h"
#include "usart/usart.h"
#include "twi/twi_master.h"

#include <util/twi.h>


// ****************** DEFINITION ***********************************************************
#ifndef TWI_FREQ
#define TWI_FREQ        100000L
#endif

#define SLAVE_ADDRESS   20

// ****************** Global variables ******************************************************
// *****************************************************************************************

INT main (void)
{

    USART_Init ( 9600 );
    LED_1_ON

    USART_Transmit_string((unsigned char*)"0\n");

    LED_1_ON
    _delay_ms(1000);
    LED_1_OFF

//    using library
//    i2c_init();
//    USART_Transmit_string((unsigned char*)"1\n");
//    i2c_start((SLAVE_ADDRESS << 1) | I2C_READ);
//    USART_Transmit_string((unsigned char*)"2\n");
//    uint8_t readed = i2c_read_ack();
//    USART_Transmit(readed);
//    i2c_stop();

    PORTC |= _BV(4);
    PORTC |= _BV(5);

    TWSR |= _BV(TWPS0) | _BV(TWPS1);
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
    TWCR = _BV(TWEN) | _BV(TWSTA) | _BV(TWINT);
    loop_until_bit_is_set(TWCR, TWINT);

    USART_Transmit_string((unsigned char*)"1\n");

    TWDR = (SLAVE_ADDRESS << 1) + TW_READ;
    TWCR = _BV(TWEN) | _BV(TWINT);
    loop_until_bit_is_set(TWCR, TWINT);


    TWCR = _BV(TWEN) | _BV(TWINT);
    USART_Transmit_string((unsigned char*)"2\n");
    loop_until_bit_is_set(TWCR, TWINT);
    uint8_t readed = TWDR;

    TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);

    USART_Transmit(readed);
    USART_Transmit_string((unsigned char*)" END\n");

    LED_1_ON
    _delay_ms(1000);
    LED_1_OFF


    while(TRUE);
}

//******************************************************************************
//******************************************************************************

