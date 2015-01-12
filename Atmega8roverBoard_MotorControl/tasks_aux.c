#include "headers/tasks_aux.h"
#include "headers/global_types.h"

void vSetServoManualParameters(double dPeriod, double dHigh, unsigned int uiRepeater)
{
    g_stServoMenualParameters.dPeriod    = dPeriod;
    g_stServoMenualParameters.dHigh      = dHigh;
    g_stServoMenualParameters.uiRepeater = uiRepeater;
}

void vSetMotorManualParameters(UCHAR ucLeftMotorValocity, UCHAR ucRightMotorValocity, UCHAR ucLeftMotorDirection, UCHAR ucRightMotorDirection)
{
    g_stMotorMenualParameters.ucLeftMotorVelocity   = ucLeftMotorValocity;
    g_stMotorMenualParameters.ucRightMotorVelocity  = ucRightMotorValocity;
    g_stMotorMenualParameters.ucLeftMotorDirection  = ucLeftMotorDirection;
    g_stMotorMenualParameters.ucRightMotorDirection = ucRightMotorDirection;
}

BOOL bIsManualParametersChanged(UCHAR ucNewLeftMotorValocity, UCHAR ucNewRightMotorValocity, UCHAR ucNewLeftMotorDirection, UCHAR ucNewRightMotorDirection)
{
    return (
             g_stMotorMenualParameters.ucLeftMotorVelocity   != ucNewLeftMotorValocity   ||
             g_stMotorMenualParameters.ucRightMotorVelocity  != ucNewRightMotorValocity  ||
             g_stMotorMenualParameters.ucLeftMotorDirection  != ucNewLeftMotorDirection  ||
             g_stMotorMenualParameters.ucRightMotorDirection != ucNewRightMotorDirection
            );
}
