#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "headers/global_types.h"
#include "headers/task.h"
#include "headers/hardware.h"
#include "headers/usart.h"
#include "headers/lcd_jokii.h"


// ****************** DEFINITION ***********************************************************
#define RECEIVED_BYTE_BUFFER_SIZE       (32)
#define MINIMUM_DATA_RECEIVED_CNT       (7)
#define FRAME_HEADER_AND_ID             (5)                                     // length of "*:xx#"
#define DEBUG_OUTPUT                    FALSE


// ****************** Global variables ******************************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

// USART part
VUCHAR dataReceived[RECEIVED_BYTE_BUFFER_SIZE];
VUCHAR startReading     = 0;
VUCHAR lastByte         = 0;
VUCHAR vucLastFrameId      = 0;
VUINT receivedByteCount = 0;

VDOUBLE dPeriod             = 0.0;
VDOUBLE dHigh               = 0.0;
VUINT uiRepeater    = 0.0;

UINT temp = 0;
// *****************************************************************************************

INT main (void)
{
    CONFIG_SWITCH(1)                                                            // Ports for switches have to be configured before use
    CONFIG_SWITCH(2)

    LCD_Ini();
    LCD_ZapiszText("   Test LCD     ");
    LOWERLINE
    LCD_ZapiszText(" Tomasz Jokiel  ");

    vInitPipe();

//    USART_Init ( 9600 );
    USART_Init ( 1200 );
    sei();
    USART_Transmit_string((UCHAR*)"HELLO Atmega16");

//    vSetPendingTask(vBlinkDiode1);
//    vSetPendingTask(vDelay1s);
//    vSetPendingTask(vTurnOnLed1);
//    vSetPendingTask(vWaitForSwitch_1);
//    vSetPendingTask(vTurnOnLed2);
//    vSetPendingTask(vWaitForSwitch_2);
    vSetPendingTask(vTurnOffLed1);
//    vSetPendingTask(vTurnOffLed2);

    while(TRUE){
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************
/**
 * Interrupt handler for USART receive
 */
ISR(USART_RXC_vect)
{
    //  LED_1_TOGGLE
    //  LED_1_OFF
    UCHAR byte = UDR;
    UCHAR ucFrameId = 0;
#if DEBUG_OUTPUT
    unsigned char buffer[10] = {0};
#endif // DEBUG_OUTPUT

    if((lastByte == '*') && (byte == ':') && (receivedByteCount == 0))          //Detect Start frame
    {
        dataReceived[receivedByteCount++] = lastByte;
    }

    if(receivedByteCount > 0)
    {
        dataReceived[receivedByteCount++] = byte;
        if(receivedByteCount == RECEIVED_BYTE_BUFFER_SIZE) {
            receivedByteCount--;
        }

    }


    if((lastByte == ':') && (byte == '#') && (receivedByteCount > MINIMUM_DATA_RECEIVED_CNT)){  // Detect end frame
        dataReceived[receivedByteCount++] = 0x00;                               // Put zero string terminator at the end
#if DEBUG_OUTPUT
        USART_Transmit_string((unsigned char*)dataReceived);
#endif // DEBUG_OUTPUT
        receivedByteCount = 0;

//        if(0 == strcmp("*:START:#", (char*)dataReceived)){
//            USART_Transmit_string((unsigned char*)"*:SERVO_READY:#");
//            lastByte = byte;
//            LED_2_ON
//            return;
//        }



#if DEBUG_OUTPUT
        if(dataReceived[2] == 'P'){
            USART_Transmit_string((unsigned char*)"Period = ");

            dataReceived[3] -= '0';
            dataReceived[4] -= '0';
            dataReceived[5] -= '0';

            temp = dataReceived[3]*100 + dataReceived[4]*10 + dataReceived[5];

            dPeriod = ((double)temp)*0.1;

            sprintf((char *)buffer, "%d ", temp);
            USART_Transmit_string(buffer);
        }
        if(dataReceived[6] == 'H'){
            USART_Transmit_string((unsigned char*)"HIGH = ");

            dataReceived[7] -= '0';
            dataReceived[8] -= '0';
            dataReceived[9] -= '0';

            temp = dataReceived[7]*100 + dataReceived[8]*10 + dataReceived[9];
            dHigh = ((double)temp)*0.1;

            sprintf((char *)buffer, "%d ", temp);
            USART_Transmit_string(buffer);
        }
        if(dataReceived[10] == 'R'){
            USART_Transmit_string((unsigned char*)"Repeater = ");

            dataReceived[11] -= '0';
            dataReceived[12] -= '0';
            dataReceived[13] -= '0';

            uiRepeater = dataReceived[11]*100 + dataReceived[12]*10 + dataReceived[13];

            sprintf((char *)buffer, "%d ", uiRepeater);
            USART_Transmit_string(buffer);

            // Send Acknowledge
            USART_Transmit_string((unsigned char*)"*:ACK:#");

            // run servo task
            vSetPendingTask(vServoManual);
        }
#else // DEBUG_OUTPUT
//        if( (dataReceived[2]  == 'P')
//                &&
//                (dataReceived[6]  == 'H')
//                &&
//                (dataReceived[10] == 'R')){
//
//            // PERIOD
//            dataReceived[3] -= '0';
//            dataReceived[4] -= '0';
//            dataReceived[5] -= '0';
//
//            temp = dataReceived[3]*100 + dataReceived[4]*10 + dataReceived[5];
//            dPeriod = ((double)temp)*0.1;
//
//            // HIGH state
//            dataReceived[7] -= '0';
//            dataReceived[8] -= '0';
//            dataReceived[9] -= '0';
//
//            temp = dataReceived[7]*100 + dataReceived[8]*10 + dataReceived[9];
//            dHigh = ((double)temp)*0.1;
//
//            // REPEATER
//            dataReceived[11] -= '0';
//            dataReceived[12] -= '0';
//            dataReceived[13] -= '0';
//
//            uiRepeater = dataReceived[11]*100 + dataReceived[12]*10 + dataReceived[13];
//
//            // Send Acknowledge
//            USART_Transmit_string((unsigned char*)"*:ACK:#");
//            // run servo task
//            vSetPendingTask(vServoManual);
//        }else
        {
            // decode frame id
            dataReceived[2] -= '0';
            dataReceived[3] -= '0';

            ucFrameId = dataReceived[2]*10 + dataReceived[3];

            if(ucFrameId != vucLastFrameId)
            {
                vSetPendingTask(vBlinkDiode1);
                LCD_Czysc();
                LCD_ZapiszText((CHAR*) (dataReceived + FRAME_HEADER_AND_ID));

                vucLastFrameId = ucFrameId;
            }
        }
#endif // DEBUG_OUTPUT
    }

    lastByte = byte;
}



/*
PROTOCOL:
Start Frame - *:
P           - period: x*0.1ms
H           - high state: y*0.1ms
R           - repeat: z times
End frame   - :#

*:PxxxHyyyRzzz:#

Example
*:P200H020R100:#
Period:  20.0 ms
HIGH:     2.0 ms
Repeat: 100 times

 */

/*
PROTOCOL RF:

*:xx#message:#

Example
*:10#message:#
Frame id:       10

 */
