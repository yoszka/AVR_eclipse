#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "headers/global_types.h"
#include "headers/hardware.h"
#include "headers/usart.h"
#include "headers/adc.h"


// ****************** DEFINITION ***********************************************************
// ****************** Global variables ******************************************************
// *****************************************************************************************

INT main (void)
{

    ADC_Init();
    USART_Init ( 9600 );
    LED_1_ON

    sei();
    USART_Transmit_string((unsigned char*)"ATmega8 test board");
    LED_1_ON
    ADC_Start();


    while(TRUE);
}

//******************************************************************************
//******************************************************************************
ISR(USART_RXC_vect)
{
    unsigned char byte = UDR;
//    LED_1_TOGGLE
}


ISR(ADC_vect)
{
    LED_2_TOGGLE
    unsigned char adcValue = ADC_get8bitValue();

    if(adcValue > 70)
    {
        LED_1_ON;
    }
    else
    {
        LED_1_OFF
    }
    USART_Transmit(adcValue);
    ADC_Disable();
//    ADC_Start();
    _delay_ms(100);

}
