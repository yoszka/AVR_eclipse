/*  interrupt_handlers.c
 *
 *  Created on: 26.10.2013
 *      Author: Tomasz Jokiel
 */

#include <avr/interrupt.h>
#include "headers/util.h"
#include "headers/global_types.h"
#include "lcd/lcd_jokii.h"
#include "system/task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ****************** DEFINITION ***********************************************
#define RECEIVED_BYTE_BUFFER_SIZE       (32)
#define MINIMUM_DATA_RECEIVED_CNT       (7)
#define FRAME_HEADER_AND_ID             (5)                                     // length of "*:xx#"
#define FRAME_ID_POS_START              (2)                                     // position in raw frame where id value starts
#define FRAME_ID_POS_END                (3)                                     // position in raw frame where id value ends
#define FRAME_ID_LENGTH                 (FRAME_ID_POS_END - FRAME_ID_POS_START + 1)// position in raw frame where id value ends
#define FRAME_PROT_VER_POS              (5)                                     // position in raw frame where protocol value present
#define FRAME_CRC16_LSB_POS             (7)                                     // position in raw frame where CRC16 value LSB
#define FRAME_CRC16_MSB_POS             (8)                                     // position in raw frame where CRC16 value MSB
#define FRAME_CRC16_LENGTH              (2)                                     // length of CRC16 value in bytes
#define FRAME_DATA_START                (10)                                    // position in raw frame where payload data starts
#define BYTE_LENGTH                     (8)                                     // number of bits in byte
#define START_SEQ_LEN                   (2)                                     // length of start sequence "*:"
#define STOP_SEQ_LEN                    (2)                                     // length of stop sequence ":#"
#define DELIMITER_SEQ_LEN               (1)                                     // delimiter sequence length "#"
#define FRAME_PROT_VER_LEN              (1)                                     // frame protocol version length
#define _16_BIT_LSB_MASK                (0x00FF)                                // mask for 16-bit value (UINT) for LSB

#define START_SEQ                       "*:"                                    // start sequence "*:"
#define STOP_SEQ                        ":#"                                    // stop sequence ":#"
#define DELIMITER_SEQ                    "#"                                    // delimiter sequence "#"

// ****************** Global variables *****************************************
VUCHAR avucDataReceived[RECEIVED_BYTE_BUFFER_SIZE];

// USART part
VUCHAR vucLastByte          = 0;
VUCHAR vucLastFrameId       = 0;
VUINT  vuiReceivedByteCount = 0;

// ****************** Typedefs *************************************************

typedef struct{
    UCHAR  ucId;          // Frame id (integer in range 10-99)
    UCHAR  ucProtVer;     // Protocol version (integer in range 0-9)
    UINT   uiCrc16;       // CRC16  (16-bit value)
    UCHAR* pucData;       // pointer to data buffer
    UCHAR  ucDataLength;  // data length
}RF_FRAME;

// ****************** Declarations *********************************************

RF_FRAME stDecodeFrame(UCHAR* pucRawFrameData, UCHAR ucLength);
UCHAR ucEncodeFrame(RF_FRAME stFrame, UCHAR* pucRfDataBuffer);

// *****************************************************************************
// *****************************************************************************

/**
 * Interrupt handler for USART receive

   PROTOCOL RF:

   *:xx#payload:#

   Example
   *:10#payload:#
   Frame id:       10

 */
ISR(USART_RXC_vect)
{
    UCHAR byte = UDR;

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

        RF_FRAME stFrame = stDecodeFrame((UCHAR*)avucDataReceived, (UCHAR)vuiReceivedByteCount);
        UINT uiCrcTmp = uiCRC16(stFrame.pucData, stFrame.ucDataLength);             // Calculate CRC
        vuiReceivedByteCount = 0;

        if((stFrame.ucId != vucLastFrameId) && (uiCrcTmp == stFrame.uiCrc16))
        {
            vSetPendingTask(vTask_BlinkDiode1);
            LCD_Czysc();
            memcpy((void*)avucDataReceived, stFrame.pucData, stFrame.ucDataLength);
            avucDataReceived[stFrame.ucDataLength] = 0;

            LCD_ZapiszText((CHAR*) avucDataReceived);

            vucLastFrameId = stFrame.ucId;
        }

    }

    vucLastByte = byte;
}

void vEnableInterrupts(void){
    sei();
}

/**
 * Frame decoder

   PROTOCOL RF v2:

   *:xx#p#LM#payload:#

   Example
   *:10#2#LM#payload:#

   Frame id:            10
   Protocol version:    2
   CRC16:               LM // 16 bit crc value - not printed sign, L - LSB; M - MSB

   @param       pucInputData pointer to raw frame data
   @param       ucLength     length of raw frame data
   @side effect destroy original frame data
 */
RF_FRAME stDecodeFrame(UCHAR* pucRawFrameData, UCHAR ucLength){
    RF_FRAME stFrame = {};

    pucRawFrameData[FRAME_ID_POS_START] -= '0';
    pucRawFrameData[FRAME_ID_POS_END]   -= '0';

    stFrame.ucId = pucRawFrameData[FRAME_ID_POS_START]*10
                 + pucRawFrameData[FRAME_ID_POS_END];                           // Calculate frame ID

    stFrame.ucProtVer = pucRawFrameData[FRAME_PROT_VER_POS]   -= '0';           // Retrieve protocol version

    stFrame.uiCrc16  = pucRawFrameData[FRAME_CRC16_MSB_POS] << BYTE_LENGTH;
    stFrame.uiCrc16 += pucRawFrameData[FRAME_CRC16_LSB_POS];

    stFrame.pucData = pucRawFrameData + FRAME_DATA_START;

    stFrame.ucDataLength = (pucRawFrameData + ucLength)                         // End of raw frame data
                            - STOP_SEQ_LEN                                      // cut stop sequence
                            - stFrame.pucData;                                  // payload data position start

    return stFrame;
}

/**
 * Encode data from {@code stFrame}, and put raw data to {@code pucRfDataBuffer}
 * DON'T FORGET freepucRfDataBuffer.
 * @return length of data in pucRfDataBuffer
 */
UCHAR ucEncodeFrame(RF_FRAME stFrame, UCHAR* pucRfDataBuffer){
    // *:xx#p#LM#payload:#

    UCHAR ucDataLength =  START_SEQ_LEN                                         // *:
                        + FRAME_ID_LENGTH                                       // xx
                        + DELIMITER_SEQ_LEN                                     // #
                        + FRAME_PROT_VER_LEN                                    // p
                        + DELIMITER_SEQ_LEN                                     // #
                        + FRAME_CRC16_LENGTH                                    // LM
                        + DELIMITER_SEQ_LEN                                     // #
                        + stFrame.ucDataLength                                  // payload
                        + STOP_SEQ_LEN;                                         // :#

    pucRfDataBuffer = malloc(ucDataLength);

    if(pucRfDataBuffer != NULL){
        sprintf((CHAR*)pucRfDataBuffer, START_SEQ"%02d"DELIMITER_SEQ"%d"DELIMITER_SEQ, stFrame.ucId, stFrame.ucProtVer); // *:xx#p#
        pucRfDataBuffer[FRAME_CRC16_LSB_POS] =  stFrame.uiCrc16                 & _16_BIT_LSB_MASK;                      // L
        pucRfDataBuffer[FRAME_CRC16_MSB_POS] = (stFrame.uiCrc16 >> BYTE_LENGTH) & _16_BIT_LSB_MASK;                      // M

        memcpy((pucRfDataBuffer + FRAME_CRC16_MSB_POS + 1),                 DELIMITER_SEQ,   DELIMITER_SEQ_LEN);         // #
        memcpy((pucRfDataBuffer + FRAME_DATA_START),                        stFrame.pucData, stFrame.ucDataLength);      // payload
        memcpy((pucRfDataBuffer + FRAME_DATA_START + stFrame.ucDataLength), STOP_SEQ,        STOP_SEQ_LEN);              // :#

    }else{
        ucDataLength = 0;
    }
    return ucDataLength;
}
