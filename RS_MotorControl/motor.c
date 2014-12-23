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

void vLeftMotorStop(void)
{
//    if(!(g_stMotorMenualParameters.ucLeftMotorValocity  == 0  &&      // if not already stopped (in middle position)
//         /*g_stMotorMenualParameters.ucRightMotorValocity == 0*/ TRUE))
//    {
//        //
//        vSetMotorManualParameters(0, 0, '+', '+');
//        // run motor task
//        vSetPendingTask(vMotorManualMockBServo);
//    }

    if(!(g_stMotorMenualParameters.ucLeftMotorValocity  == 0  &&      // if not already stopped (in middle position)
         /*g_stMotorMenualParameters.ucRightMotorValocity == 0*/ TRUE))
    {
        vSetMotorManualParameters(0, 0, '+', '+');
        setSoftPWMvalueTimer1(0);
    }
}
