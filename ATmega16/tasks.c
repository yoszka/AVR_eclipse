#include "headers/global_types.h"
#include "headers/task.h"
#include <util/delay.h>
#include "headers/hardware.h"

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
//    LED_1_ON
    LED_ON(1)
}

void vTurnOffLed1(void){
    LED_1_OFF
}

void vTurnOnLed2(void){
//    LED_2_ON
    LED_ON(2)
}

void vTurnOffLed2(void){
    LED_2_OFF
}

//void vTurnOnLed3(void){
//	LED_3_ON
//}
//
//void vTurnOffLed3(void){
//	LED_3_OFF
//}

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
//      _delay_us(dHigh);
        LED_1_OFF
        _delay_ms(dPeriod);
    }
}

void vWaitForSwitch_1(void){

    WAIT_FOR_SWITCH_1
//    WAIT_FOR_SWITCH(1)
//    WAIT_FOR_SWITCH2(1);
}
