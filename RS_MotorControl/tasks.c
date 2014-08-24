#include "headers/global_types.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include <util/delay.h>
#include "headers/hardware.h"

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

    for (int i = 0; i < g_stServoMenualParameters.uiRepeater; i++){
        LED_1_ON
        _delay_ms(g_stServoMenualParameters.dHigh);
        //        _delay_us(dHigh);
        LED_1_OFF
        _delay_ms(g_stServoMenualParameters.dPeriod);
    }
}

void vMotorManual(void)
{
    #define DEFAULT_REPEATER    50
    #define DEFAULT_PERIOD      20.0

    double dHigh;   // responsible for position     1.0 - middle; 1.9 - left max; 0.1 - right max

//    g_stMotorMenualParameters.ucLeftMotorValocity
//    g_stMotorMenualParameters.ucRightMotorValocity    // not used now
//    g_stMotorMenualParameters.ucLeftMotorDirection
//    g_stMotorMenualParameters.ucRightMotorDirection   // not used now

    double dVelocityAbs = ((double)g_stMotorMenualParameters.ucLeftMotorValocity / 255.0) * 0.9;

    if(g_stMotorMenualParameters.ucLeftMotorDirection == '+')
    {
        dHigh = 1.0 + dVelocityAbs;
    }
    else
    {
        dHigh = 1.0 - dVelocityAbs;
    }


    vSetServoManualParameters(DEFAULT_PERIOD, dHigh, DEFAULT_REPEATER);
    vServoManual();
}
