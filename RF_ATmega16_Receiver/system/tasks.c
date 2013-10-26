/*  tasks.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#include "../headers/global_types.h"
#include "task.h"
#include <util/delay.h>
#include "../headers/hardware.h"

// ****************** Global variables *****************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

/**
 * Delay 1s
 */
void vTaks_Delay1s(void){
    for(int i = 0; i < 100; i++){
        _delay_ms(10);
    }
}

void vTaks_TurnOnLed1(void){
    LED_ON(1)
}

void vTaks_TurnOffLed1(void){
    LED_OFF(1)
}

void vTaks_TurnOnLed2(void){
    LED_ON(2)
}

void vTaks_TurnOffLed2(void){
    LED_OFF(2)
}

/**
 * Wait for SWITCH 1 - block queue
 */
void vTaks_WaitForSwitch_1(void){

    WAIT_FOR_SWITCH(1)
}

/**
 * Wait for SWITCH 2 - block queue
 */
void vTask_WaitForSwitch_2(void){
    WAIT_FOR_SWITCH(2)
}

void vTask_BlinkDiode1(void){

    LED_TOGGLE(1)
    _delay_ms(1000);
    LED_TOGGLE(1)

}
