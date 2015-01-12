/*
 * motor.c
 *
 *  Created on: 26-08-2014
 *      Author: Tomasz Jokiel
 */

#include "headers/motor.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include "headers/global_types.h"
#include "headers/timer.h"

extern volatile uint8_t g_ucSoftPWMTimer1Hign;
extern volatile uint8_t g_ucSoftPWMTimer2High;

void vLeftMotorStop(void)
{
    if(g_stMotorMenualParameters.ucLeftMotorVelocity  != 0 || g_ucSoftPWMTimer1Hign != 0)// if not already stopped (in middle position)
    {
        vSetMotorManualParameters(0, g_stMotorMenualParameters.ucRightMotorVelocity, '+', g_stMotorMenualParameters.ucRightMotorDirection);
        setSoftPWMvalueTimer1(0);
    }
}

void vRightMotorStop(void)
{
    if(g_stMotorMenualParameters.ucRightMotorVelocity  != 0 || g_ucSoftPWMTimer2High != 0)// if not already stopped (in middle position)
    {
        vSetMotorManualParameters(g_stMotorMenualParameters.ucLeftMotorVelocity, 0, g_stMotorMenualParameters.ucLeftMotorDirection, '+');
        setSoftPWMvalueTimer2(0);
    }
}
