#include "headers/global_types.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include <util/delay.h>
#include "headers/hardware.h"
#include "headers/timer.h"
#include "headers/adc.h"
#include "headers/usart.h"

#define MAX_VELOCITY 240

/**
 * Delay 1s
 */
void vDelay1s(void){
    for(int i = 0; i < 100; i++){
        _delay_ms(10);
    }
}


void vTurnOnLed(void){
    LED_ON
}

void vTurnOffLed(void){
    LED_OFF
}

void vMotorManual(void)
{
    UCHAR ucVelocity = 0;

    // LEFT motor
    if(g_stMotorMenualParameters.ucLeftMotorDirection == '+')
    {
        MOTOR_1_DIR_LEFT
    }
    else
    {
        MOTOR_1_DIR_RIGHT
    }

    ucVelocity = g_stMotorMenualParameters.ucLeftMotorVelocity;

    if(ucVelocity > MAX_VELOCITY) {
        ucVelocity = MAX_VELOCITY;
    }

    setSoftPWMvalueTimer1(ucVelocity);

    // RIGHT motor
    ucVelocity = 0;

    if(g_stMotorMenualParameters.ucRightMotorDirection == '+')
    {
        MOTOR_2_DIR_LEFT
    }
    else
    {
        MOTOR_2_DIR_RIGHT
    }

    ucVelocity = g_stMotorMenualParameters.ucRightMotorVelocity;

    if(ucVelocity > MAX_VELOCITY) {
        ucVelocity = MAX_VELOCITY;
    }

    setSoftPWMvalueTimer2(ucVelocity);
}

void vInfSysCmdReady(void)
{
    USART_Transmit_string((unsigned char*)"*:SC READY:#");
}

void vAdcReady(void)
{
//    unsigned char aucToSend[] = "*:ACK&ADC&J:#";
//    aucToSend[10] = g_ucAdcValue;
    unsigned char aucToSend[] = "*:ACK&ADC&000:#";
    aucToSend[10] = '0' + g_ucAdcValue/100;
    aucToSend[11] = '0' + (g_ucAdcValue%100)/10;
    aucToSend[12] = '0' + (g_ucAdcValue%10);
    USART_Transmit_string((unsigned char*)aucToSend);
}

void vSysCmdMeasureAdc(void)
{
    ADC_Enable();
    ADC_Start();
}
