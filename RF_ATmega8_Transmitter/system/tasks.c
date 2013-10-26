/*  tasks.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#include "../headers/global_types.h"
#include "task.h"
#include <util/delay.h>
#include "../headers/hardware.h"
#include "../headers/usart.h"
#include <stdio.h>


/**
 * Delay 1s
 */
void vTask_Delay1s(void){
    for(int i = 0; i < 100; i++){
        _delay_ms(10);
    }
}

void vTask_TurnOnLed1(void){
    LED_1_ON
}

void vTask_TurnOffLed1(void){
    LED_1_OFF
}

void vTask_TurnOnLed2(void){
    LED_2_ON
}

void vTask_TurnOffLed2(void){
    LED_2_OFF
}

void vTask_TurnOnLed3(void){
    LED_3_ON
}

void vTask_TurnOffLed3(void){
    LED_3_OFF
}

/**
 * Wait for SWITCH 1 - block queue
 */
void vTask_WaitForSwitch1(void){
    WAIT_FOR_SWITCH(1)
}

void vTask_TramssmitAfterButtonPush(void){
    UCHAR i = 10;
    UCHAR buffer[40] = {};

    while(TRUE){
        WAIT_FOR_SWITCH(1)

        sprintf((char *)buffer, (const char *)"*:%d#Tomek %d:#", i, i);         // Prepare string for send

        for(UCHAR i = 0; i < 5; i++){                                           // Retransmit 5 times
            USART_Transmit_string((UCHAR*)buffer);
        }

        i = (i+1) % 100;                                                        // Calculate ID from range 10-99
        i = (i < 10) ? (i + 10) : i;
    }
}
