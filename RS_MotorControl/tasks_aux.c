#include "headers/tasks_aux.h"

void vSetServoManualParameters(double dPeriod, double dHigh, unsigned int uiRepeater)
{
    g_stServoMenualParameters.dPeriod    = dPeriod;
    g_stServoMenualParameters.dHigh      = dHigh;
    g_stServoMenualParameters.uiRepeater = uiRepeater;
}

void vSetMotorManualParameters(UCHAR ucLeftMotorValocity, UCHAR ucRightMotorValocity, UCHAR ucLeftMotorDirection, UCHAR ucRightMotorDirection)
{
    g_stMotorMenualParameters.ucLeftMotorValocity   = ucLeftMotorValocity;
    g_stMotorMenualParameters.ucRightMotorValocity  = ucRightMotorValocity;
    g_stMotorMenualParameters.ucLeftMotorDirection  = ucLeftMotorDirection;
    g_stMotorMenualParameters.ucRightMotorDirection = ucRightMotorDirection;
}
