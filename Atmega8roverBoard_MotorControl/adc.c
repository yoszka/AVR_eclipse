/*
 * adc.c
 *
 *  Created on: 22-01-2014
 *      Author: Tomasz Jokiel
 */
#include <avr/io.h>
#include "headers/adc.h"

void ADC_Init()
{
    ADCSRA = (1 << ADEN)  | (1 << ADIE)  |                 // enable ADC device; ADIE - enable interrupts
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // ADPS2:0 prescaler 128

    ADMUX = (1 << ADLAR) | (1 << MUX2)                     // ADC lef adjust -> can use ADCH for 8-bit value, ADC4
          | (1 << REFS0) | (1 << REFS1);                   // Internal reference voltage 2.56 V

    DDRC &= ~(1 << PC4);
}

void ADC_Enable()
{
    ADCSRA |= (1 << ADEN);
}

void ADC_Disable()
{
    ADCSRA &= ~(1 << ADEN);
}

void ADC_Start()
{
    ADCSRA |= (1 << ADSC);
}

void ADC_Stop()
{
    ADCSRA &= ~(1 << ADSC);
}

unsigned char ADC_get8bitValue()
{
    return ADCH;
}
