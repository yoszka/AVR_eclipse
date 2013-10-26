/*  main.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include "headers/global_types.h"
#include "headers/interrupt_handlers.h"
#include "system/task.h"
#include "headers/hardware.h"
#include "headers/usart.h"
#include "lcd/lcd_jokii.h"


// ****************** DEFINITION ***********************************************

// ****************** Global variables *****************************************

// *****************************************************************************

INT main (void)
{
    CONFIG_SWITCH(1)                                                            // Ports for switches have to be configured before use
    CONFIG_SWITCH(2)

    LCD_Ini();
    LCD_ZapiszText("   Test LCD     ");
    LOWERLINE
    LCD_ZapiszText(" Tomasz Jokiel  ");

    vInitPipe();

    USART_Init ( USART_BAUD_RATE );
    vEnableInterrupts();
    USART_Transmit_string((UCHAR*)"HELLO Atmega16");                            // Transmit hello via USART

    vSetPendingTask(vTaks_TurnOffLed1);                                         // Turn off LED1

    while(TRUE){                                                                // Run task dispatcher
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************
