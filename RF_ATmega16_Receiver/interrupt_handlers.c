/*  interrupt_handlers.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "lcd/lcd_jokii.h"
#include "system/task.h"

// ****************** DEFINITION ***********************************************
#define RECEIVED_BYTE_BUFFER_SIZE       (32)
#define MINIMUM_DATA_RECEIVED_CNT       (7)
#define FRAME_HEADER_AND_ID             (5)                                     // length of "*:xx#"

// ****************** Global variables *****************************************
VUCHAR avucDataReceived[RECEIVED_BYTE_BUFFER_SIZE];

// USART part
VUCHAR vucLastByte          = 0;
VUCHAR vucLastFrameId       = 0;
VUINT  vuiReceivedByteCount = 0;

// *****************************************************************************
// *****************************************************************************

/**
 * Interrupt handler for USART receive

   PROTOCOL RF:

   *:xx#message:#

   Example
   *:10#message:#
   Frame id:       10

 */
ISR(USART_RXC_vect)
{
    UCHAR byte = UDR;
    UCHAR ucFrameId = 0;

    if((vucLastByte == '*') && (byte == ':') && (vuiReceivedByteCount == 0))    //Detect Start frame
    {
        avucDataReceived[vuiReceivedByteCount++] = vucLastByte;
    }

    if(vuiReceivedByteCount > 0)                                                // If true then start collecting data
    {
        avucDataReceived[vuiReceivedByteCount++] = byte;
        if(vuiReceivedByteCount == RECEIVED_BYTE_BUFFER_SIZE) {
            vuiReceivedByteCount--;
        }

    }


    if((vucLastByte == ':') && (byte == '#')                                    // Detect end frame
            && (vuiReceivedByteCount > MINIMUM_DATA_RECEIVED_CNT)){

        avucDataReceived[vuiReceivedByteCount++] = 0x00;                        // Put zero string terminator at the end
        vuiReceivedByteCount = 0;

        // Decode frame id. Since radio channel is very noisy need to retransmit
        // same frame multiple times. Next received frames with same ID will be
        // skipped.
        avucDataReceived[2] -= '0';
        avucDataReceived[3] -= '0';

        ucFrameId = avucDataReceived[2]*10 + avucDataReceived[3];               // Calculate frame ID

        if(ucFrameId != vucLastFrameId)
        {
            vSetPendingTask(vTask_BlinkDiode1);
            LCD_Czysc();
            LCD_ZapiszText((CHAR*) (avucDataReceived + FRAME_HEADER_AND_ID));

            vucLastFrameId = ucFrameId;
        }
    }

    vucLastByte = byte;
}

void vEnableInterrupts(void){
    sei();
}
