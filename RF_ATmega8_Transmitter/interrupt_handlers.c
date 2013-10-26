/*  interrupt_handlers.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "system/task.h"

// ****************** DEFINITION ***********************************************

// ****************** Global variables *****************************************

// *****************************************************************************
// *****************************************************************************

/**
 * Interrupt handler for USART receive
 */
//ISR(USART_RXC_vect)
//{
//    unsigned char byte = UDR;
//}

void vEnableInterrupts(void){
    sei();
}
