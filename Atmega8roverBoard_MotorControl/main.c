#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include "headers/usart.h"
#include "headers/protocol.h"
#include "headers/timer.h"
#include "headers/motor.h"

//#include "headers/hardware.h"
//#include <util/delay.h>


// ****************** DEFINITION ***********************************************************
#define MOTOR_MIDDLE_POS_STOP       20.0, 1.0, 100

// ****************** Global variables ******************************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

volatile ST_SERVO_MANUAL_PARAMETERS g_stServoMenualParameters = {0.0, 0.0 ,0};
volatile ST_MOTOR_MANUAL_PARAMETERS g_stMotorMenualParameters = {0, 0, 0, 0};

// *****************************************************************************************

//#error "Not ready!!"
INT main (void)
{
    vInitPipe();

//    MOTOR_1_DIR_LEFT
//    MOTOR_1_ENA_HI
//    MOTOR_2_DIR_LEFT
//    MOTOR_2_ENA_HI
//
//
//    _delay_ms(1000);
//    MOTOR_1_ENA_LOW
//    MOTOR_2_ENA_LOW

    USART_Init ( 9600 );
    initTimer0();
    setSoftPWMvalueTimer1(0);
    setSoftPWMvalueTimer2(0);
    initTimerMotorTimers();

    //
//    vSetServoManualParameters(MOTOR_MIDDLE_POS_STOP);
//    // run motor task
//    vSetPendingTask(vServoManual);

    sei();
    //USART_Transmit_string((unsigned char*)"*:SERVO_READY:#");

    while(TRUE)
    {
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************
ISR(USART_RXC_vect)
{
//    bHandleInput(bServoManualHandler, UDR);
    BOOL bHandled = bHandleInput(bMotorManualHandler, UDR);

    if(bHandled)
    {
        resetTimer0();
    }
}
