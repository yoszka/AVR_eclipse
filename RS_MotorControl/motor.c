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

void vLeftMotorStop(void)
{
    if(g_stMotorMenualParameters.ucLeftMotorValocity  != 0)// if not already stopped (in middle position)
    {
        vSetMotorManualParameters(0, 0, '+', '+');
        setSoftPWMvalueTimer1(0);
    }
}
