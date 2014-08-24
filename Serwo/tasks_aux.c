#include "headers/tasks_aux.h"

void vSetServoManualParameters(double dPeriod, double dHigh, unsigned int uiRepeater)
{
    g_stServoMenualParameters.dHigh      = dHigh;
    g_stServoMenualParameters.dPeriod    = dPeriod;
    g_stServoMenualParameters.uiRepeater = uiRepeater;
}
