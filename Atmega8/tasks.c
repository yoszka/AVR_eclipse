#include "headers/global_types.h"
#include "headers/task.h"
#include <util/delay.h>
#include "headers/hardware.h"
#include "headers/usart.h"
#include <stdio.h>

extern volatile double dPeriod;
extern volatile double dHigh;
extern volatile unsigned int uiRepeater;

/**
 * Delay 1s
 */
void vDelay1s(void){
    for(int i = 0; i < 100; i++){
        _delay_ms(10);
    }
}


void vTurnOnLed1(void){
    LED_1_ON
}

void vTurnOffLed1(void){
    LED_1_OFF
}

void vTurnOnLed2(void){
    LED_2_ON
}

void vTurnOffLed2(void){
    LED_2_OFF
}

void vTurnOnLed3(void){
    LED_3_ON
}

void vTurnOffLed3(void){
    LED_3_OFF
}

void vServoP(void){

    for (int i = 0; i < 8; i++){
        LED_1_ON
        _delay_ms(0.2);
        LED_1_OFF
        _delay_ms(20.0);
    }
}


void vServoS(void){

    for (int i = 0; i < 13; i++){
        LED_1_ON
        _delay_ms(1.9);
        LED_1_OFF
        _delay_ms(20.0);
    }
}


void vServoL(void){

    for (int i = 0; i < 8; i++){
        LED_1_ON
        _delay_ms(2.5);
        LED_1_OFF
        _delay_ms(20.0);
    }
}

void vServoManual(void){

    for (int i = 0; i < uiRepeater; i++){
        LED_1_ON
        _delay_ms(dHigh);
        //		_delay_us(dHigh);
        LED_1_OFF
        _delay_ms(dPeriod);
    }
}

void vTask_WaitForSwitch1(void){
    WAIT_FOR_SWITCH(1)
}

void vTask_TramssmitAfterButtonPush(void){
    UCHAR i = 10;
    UCHAR buffer[40] = {};

    while(TRUE){
        WAIT_FOR_SWITCH(1)

        sprintf((char *)buffer, (const char *)"*:%d#Tomek %d:#", i, i);

        for(UCHAR i = 0; i < 5; i++){                                           // Retransmit 5 times
            USART_Transmit_string((UCHAR*)buffer);
        }

        i = (i+1) % 100;
        i = (i < 10) ? (i + 10) : i;
    }
}
