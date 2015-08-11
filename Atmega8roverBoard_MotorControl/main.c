/*
 * main.c
 *
 *      Author: Tomasz Jokiel
 */

#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include "headers/usart.h"
#include "headers/protocol.h"
#include "headers/timer.h"
#include "headers/motor.h"
#include "headers/adc.h"


// ****************** DEFINITION ***********************************************************
#define MOTOR_MIDDLE_POS_STOP       20.0, 1.0, 100

// ****************** Global variables ******************************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

volatile ST_SERVO_MANUAL_PARAMETERS g_stServoMenualParameters = {0.0, 0.0 ,0};
volatile ST_MOTOR_MANUAL_PARAMETERS g_stMotorMenualParameters = {0, 0, 0, 0};
volatile UCHAR g_ucAdcValue = 0;

// *****************************************************************************************

INT main (void)
{
    vInitPipe();

    ADC_Init();
    USART_Init ( 9600 );
    initTimer0();
    setSoftPWMvalueTimer1(0);
    setSoftPWMvalueTimer2(0);
    initTimerMotorTimers();

    sei();
    USART_Transmit_string((UCHAR*)"*:rOvEr RADY:#");

    while(TRUE)
    {
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************
ISR(USART_RXC_vect)
{
    BOOL bHandled = bHandleInput(bMotorManualHandler, UDR);

    if(bHandled)
    {
        resetTimer0();
    }
}


ISR(ADC_vect)
{
    g_ucAdcValue = ADC_get8bitValue();
    vSetPendingTask(vAdcReady);
    ADC_Disable();
}
