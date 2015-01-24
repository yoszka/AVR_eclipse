#include <string.h>

#include "headers/global_types.h"
#include "headers/protocol.h"
#include "headers/hardware.h"
#include "headers/usart.h"
#include "headers/task.h"
#include "headers/tasks_aux.h"
#include "headers/util.h"

// ****************** DEFINITION ***********************************************************
#define RECEIVED_BYTE_BUFFER_SIZE       (32)
#define MINIMUM_DATA_RECEIVED_CNT       (5)
#define DEBUG_OUTPUT                    FALSE


// ****************** Static variables ******************************************************
// USART part
static volatile unsigned char aucDataReceived[RECEIVED_BYTE_BUFFER_SIZE];
static volatile unsigned char ucLastByte = 0;
static volatile unsigned int  uiReceivedByteCount = 0;

// ****************** Implementation ********************************************************

BOOL bHandleInput(T_PROTOCOL_HANDLER_FUNCTION bProtocolHandler, UCHAR ucInputByte)
{
    return bProtocolHandler(ucInputByte);
}



/**
 * Handler for MOTOR controller
 */

/*
PROTOCOL:
Start Frame - *:
GO          - protocol function "GO"
d           - direction "+" forward, "-" backward
xxx         - velocity for left motor 0-255
yyy         - velocity for right motor 0-255
End frame   - :#

*:GOdxxx&dyyy:#

Example
*:GO+150&+150:#

Means: Go forward for 150/255 max velocity (left and right motors same velocity)

*/

/**
 * Handler for external system commands
 */

/*
PROTOCOL:
Start Frame - *:
SC          - protocol function "S"
xxx         - system command 0-255
End frame   - :#

*:SCxxx:#

Example
*:SC001:#

*/
BOOL bMotorManualHandler(UCHAR ucInputByte)
{
    UCHAR ucLeftMotorValocity, ucRightMotorVelocity, ucLeftMotorDirection, ucRightMotorDirection;

#if DEBUG_OUTPUT
    unsigned char buffer[10] = {0};
#endif // DEBUG_OUTPUT

    if((ucLastByte == '*') && (ucInputByte == ':') && (uiReceivedByteCount == 0))          //Detect Start frame
    {
      aucDataReceived[uiReceivedByteCount++] = ucLastByte;
    }

    if(uiReceivedByteCount > 0)
    {
        aucDataReceived[uiReceivedByteCount++] = ucInputByte;
        if(uiReceivedByteCount == RECEIVED_BYTE_BUFFER_SIZE) uiReceivedByteCount--;
    }


    if((ucLastByte == ':') && (ucInputByte == '#') && (uiReceivedByteCount > MINIMUM_DATA_RECEIVED_CNT)){
        aucDataReceived[uiReceivedByteCount++] = 0x00;
#if DEBUG_OUTPUT
        USART_Transmit_string((unsigned char*)aucDataReceived);
#endif // DEBUG_OUTPUT
        uiReceivedByteCount = 0;

        if(0 == strcmp("*:START:#", (char*)aucDataReceived)){
            USART_Transmit_string((unsigned char*)"*:SERVO_READY:#");
            ucLastByte = ucInputByte;
            LED_ON
            return TRUE;
        }

        if((aucDataReceived[2] == 'S') &&
           (aucDataReceived[3] == 'C'))
        {
            unsigned char ucSysCmd = ucGetThreeDigitValue((unsigned char *)&(aucDataReceived[4]));

            switch(ucSysCmd)
            {
                case 1:
                    vSetPendingTask(vInfSysCmdReady);
                    break;

                case 2:
                    vSetPendingTask(vSysCmdMeasureAdc);
                    break;

                default:
                    break;
            }

            return TRUE;
        }

#if DEBUG_OUTPUT
        if(aucDataReceived[2] == 'P'){
            USART_Transmit_string((unsigned char*)"Period = ");

            aucDataReceived[3] -= '0';
            aucDataReceived[4] -= '0';
            aucDataReceived[5] -= '0';

            uiTemp = aucDataReceived[3]*100 + aucDataReceived[4]*10 + aucDataReceived[5];

            g_stServoMenualParameters.dPeriod = ((double)uiTemp)*0.1;

            sprintf((char *)buffer, "%d ", uiTemp);
            USART_Transmit_string(buffer);
        }
        if(aucDataReceived[6] == 'H'){
            USART_Transmit_string((unsigned char*)"HIGH = ");

            aucDataReceived[7] -= '0';
            aucDataReceived[8] -= '0';
            aucDataReceived[9] -= '0';

            uiTemp = aucDataReceived[7]*100 + aucDataReceived[8]*10 + aucDataReceived[9];
            g_stServoMenualParameters.dHigh = ((double)uiTemp)*0.1;

            sprintf((char *)buffer, "%d ", uiTemp);
            USART_Transmit_string(buffer);
        }
        if(aucDataReceived[10] == 'R'){
            USART_Transmit_string((unsigned char*)"Repeater = ");

            aucDataReceived[11] -= '0';
            aucDataReceived[12] -= '0';
            aucDataReceived[13] -= '0';

            g_stServoMenualParameters.uiRepeater = aucDataReceived[11]*100 + aucDataReceived[12]*10 + aucDataReceived[13];

            sprintf((char *)buffer, "%d ", g_stServoMenualParameters.uiRepeater);
            USART_Transmit_string(buffer);

            // Send Acknowledge
            USART_Transmit_string((unsigned char*)"*:ACK:#");

            // run servo task
            vSetPendingTask(vServoManual);
        }
#else // DEBUG_OUTPUT

        if((aucDataReceived[2] == 'G') &&
           (aucDataReceived[3] == 'O') &&
           (aucDataReceived[8] == '&'))
        {

            // LEFT MOTOR ------------------------
            // DIRECTION
            ucLeftMotorDirection = aucDataReceived[4];

            // VELOCITY
            ucLeftMotorValocity = ucGetThreeDigitValue((unsigned char *)&(aucDataReceived[5]));

            // RIGHT MOTOR ------------------------
            // DIRECTION
            ucRightMotorDirection = aucDataReceived[9];

            // VELOCITY
            ucRightMotorVelocity = ucGetThreeDigitValue((unsigned char *)&(aucDataReceived[10]));

            // Send Acknowledge
            USART_Transmit_string((unsigned char*)"*:ACK:#");

            if(bIsManualParametersChanged(ucLeftMotorValocity, ucRightMotorVelocity, ucLeftMotorDirection, ucRightMotorDirection))
            {
                vSetMotorManualParameters(ucLeftMotorValocity, ucRightMotorVelocity, ucLeftMotorDirection, ucRightMotorDirection);
                vSetPendingTask(vMotorManual);
            }

            return TRUE;
        }
#endif // DEBUG_OUTPUT
    }

    ucLastByte = ucInputByte;

    return FALSE;
}
