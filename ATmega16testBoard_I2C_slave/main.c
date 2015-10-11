/*  main.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include "util/delay.h"
#include "headers/hardware.h"

#include <util/twi.h>

// ****************** DEFINITION ***********************************************
#define SLAVE_ADDRESS       20

// ****************** Global variables *****************************************

// *****************************************************************************

int main (void)
{
    LED_ON(2)
    _delay_ms(1000);
    LED_OFF(2)
    _delay_ms(300);

    TWAR = (SLAVE_ADDRESS << 1) + TW_WRITE;
    TWCR = _BV(TWEN) | _BV(TWEA);
    loop_until_bit_is_set(TWCR, TWINT);

    LED_ON(2)

    TWDR = 'T';
    TWCR = _BV(TWEN) | _BV(TWINT);
    loop_until_bit_is_set(TWCR, TWINT);

    TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT);

    _delay_ms(1000);
    LED_OFF(2)

}

//******************************************************************************
//******************************************************************************
