/*
 * tasks_aux.h
 *
 *      Author: Tomasz Jokiel
 */

#ifndef TASKS_AUX_H
#define TASKS_AUX_H

#include "global_types.h"

void vSetServoManualParameters(DOUBLE dPeriod, DOUBLE dHigh, UINT uiRepeater);
void vSetMotorManualParameters(UCHAR ucLeftMotorValocity, UCHAR ucRightMotorValocity, UCHAR ucLeftMotorDirection, UCHAR ucRightMotorDirection);
BOOL bIsManualParametersChanged(UCHAR ucNewLeftMotorValocity, UCHAR ucNewRightMotorValocity, UCHAR ucNewLeftMotorDirection, UCHAR ucNewRightMotorDirection);

typedef struct
{
    DOUBLE dPeriod;
    DOUBLE dHigh;
    UINT uiRepeater;
}
ST_SERVO_MANUAL_PARAMETERS;

typedef struct
{
    UCHAR ucLeftMotorVelocity;
    UCHAR ucRightMotorVelocity;
    UCHAR ucLeftMotorDirection;
    UCHAR ucRightMotorDirection;
}
ST_MOTOR_MANUAL_PARAMETERS;

extern volatile ST_SERVO_MANUAL_PARAMETERS g_stServoMenualParameters;
extern volatile ST_MOTOR_MANUAL_PARAMETERS g_stMotorMenualParameters;
extern volatile UCHAR g_ucAdcValue;

#endif // TASKS_AUX_H
