/*
 * gpio_int.c

 *
 *  Created on: 18-02-2017
 *      Author: Tomasz Jokiel
 */
#include <stddef.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio_int.h"
#include "system.h"

#define INT_DDR        DDRD
#define INT_PORT       PORTD
#define INT_PIN        PIND
#define INT_BIT        2

pf_gpio_int_handler_t m_gpio_int_handler;

void gpio_int_init(pf_gpio_int_handler_t gpio_int_handler)
{
    m_gpio_int_handler = gpio_int_handler;

    INT_DDR  &= ~_BV(INT_BIT);     // Set as input (Using for interupt INT0)
    INT_PORT |=  _BV(INT_BIT);     // Enable pull-up resistor

    GICR  = 1 << INT0;     // Enable INT0
    MCUCR = 1 << ISC01;    // Trigger INT0 on falling edge
    sei();
}

static bool is_int_gpio_clear_for_period(uint16_t delay_ms)
{
    for(int i = 0; i < delay_ms; i++)
    {
        if(bit_is_set(INT_PIN, INT_BIT))
        {
            return false;
        }
        _delay_ms(1);
    }
    return true;
}


ISR(INT0_vect)
{
    // disable interrupts from INT0
    GICR &= ~_BV(INT0);

    if(m_gpio_int_handler != NULL && is_int_gpio_clear_for_period(200))
    {
        vSetPendingTask(m_gpio_int_handler);
    }

    // enable interrupts from INT0
    GICR |= _BV(INT0);
}
