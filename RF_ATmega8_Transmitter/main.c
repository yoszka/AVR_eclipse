/*  main.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include "headers/global_types.h"
#include "system/task.h"
#include "headers/hardware.h"
#include "headers/usart.h"
#include "headers/interrupt_handlers.h"


// ****************** DEFINITION ***********************************************

// ****************** Global variables *****************************************

// *****************************************************************************

INT main (void)
{
    CONFIG_SWITCH(1)

    vInitPipe();

    USART_Init ( USART_BAUD_RATE );

    vSetPendingTask(vTask_TurnOnLed1);
    vSetPendingTask(vTask_TramssmitAfterButtonPush);

//    vEnableInterrupts();

    while(TRUE){
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************
