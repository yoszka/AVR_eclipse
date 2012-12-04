#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "global_types.h"
#include "header_file_1.h"
#include "header_file_2.h"
#include "task.h"
#include "hardware.h"
#include "usart.h"


// ****************** DEFINITION ***********************************************************
#define RECEIVED_BYTE_BUFFER_SIZE		32


// ****************** Global variables ******************************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

// USART part
volatile unsigned char dateReceived[RECEIVED_BYTE_BUFFER_SIZE];
volatile unsigned char startReading = 0;
volatile unsigned char lastByte = 0;
volatile unsigned int receivedByteCount = 0;

volatile double dPeriod 	= 0.0;
volatile double dHigh 		= 0.0;
volatile unsigned int uiRepeater 	= 0.0;

unsigned int temp = 0;
// *****************************************************************************************

INT main (void)
{
	vInitPipe();
	
	USART_Init ( 9600 );
	sei();
	USART_Transmit_string((unsigned char*)"System READY");

//	vSetPendingTask(vDelay1s);
//	vSetPendingTask(vServoL);
//	vSetPendingTask(vDelay1s);
//	vSetPendingTask(vServoS);
//	vSetPendingTask(vDelay1s);
//	vSetPendingTask(vServoP);
//	vSetPendingTask(vDelay1s);
//	vSetPendingTask(vServoS);
//	vSetPendingTask(vDelay1s);

  while(TRUE){
	  vDispathTask();
  }

}

//******************************************************************************
//******************************************************************************
ISR(USART_RXC_vect)
{
//	LED_1_TOGGLE
//	LED_1_OFF
	unsigned char byte = UDR;
	unsigned char buffer[10] = {0};

    if((lastByte == '*') && (byte == ':') && (receivedByteCount == 0))                               //Detect Start frame
    {
      dateReceived[receivedByteCount++] = lastByte;
    }

    if(receivedByteCount > 0)
    {
    	dateReceived[receivedByteCount++] = byte;
    	if(receivedByteCount == RECEIVED_BYTE_BUFFER_SIZE) receivedByteCount--;
    }


    if((lastByte == ':') && (byte == '#') && (receivedByteCount > 10)){
    	dateReceived[receivedByteCount++] = 0x00;
    	USART_Transmit_string((unsigned char*)dateReceived);
    	receivedByteCount = 0;

    	if(dateReceived[2] == 'P'){
    		USART_Transmit_string((unsigned char*)"Period = ");
//    		USART_Transmit(dateReceived[3]);
//    		USART_Transmit(dateReceived[4]);
//    		USART_Transmit(dateReceived[5]);

    		dateReceived[3] -= '0';
    		dateReceived[4] -= '0';
    		dateReceived[5] -= '0';

    		temp = dateReceived[3]*100 + dateReceived[4]*10 + dateReceived[5];

    		dPeriod = ((double)temp)*0.1;

    		sprintf((char *)buffer, "%d ", temp);
    		USART_Transmit_string(buffer);
    	}
    	if(dateReceived[6] == 'H'){
    		USART_Transmit_string((unsigned char*)"HIGH = ");
//    		USART_Transmit(dateReceived[7]);
//    		USART_Transmit(dateReceived[8]);
//    		USART_Transmit(dateReceived[9]);

    		dateReceived[7] -= '0';
    		dateReceived[8] -= '0';
    		dateReceived[9] -= '0';

    		temp = dateReceived[7]*100 + dateReceived[8]*10 + dateReceived[9];
    		dHigh = ((double)temp)*0.1;

    		sprintf((char *)buffer, "%d ", temp);
    		USART_Transmit_string(buffer);
    	}
    	if(dateReceived[10] == 'R'){
    		USART_Transmit_string((unsigned char*)"Repeater = ");
//    		USART_Transmit(dateReceived[11]);
//    		USART_Transmit(dateReceived[12]);
//    		USART_Transmit(dateReceived[13]);

    		dateReceived[11] -= '0';
    		dateReceived[12] -= '0';
    		dateReceived[13] -= '0';

    		uiRepeater = dateReceived[11]*100 + dateReceived[12]*10 + dateReceived[13];

    		sprintf((char *)buffer, "%d ", uiRepeater);
    		USART_Transmit_string(buffer);

    		// run servo task
    		vSetPendingTask(vServoManual);
    	}

    }

    lastByte = byte;

//	dateReceived[receivedByteCount++] = byte;								// store received data into table
////	if(receivedByteCount == 881) receivedByteCount--;						// avoid exceed after array
//	USART_Transmit(byte);

}

/*
 Protocol:

 Start Frame
 0xFE 0xAA

 byte number (1)
 - period: X*0.1ms

 byte number (2)
 - HIGH state: X*0.1ms

 byte number (3)
 - repeat: X times

 End frame
0xEF 0xBB

Example:

0xFE 0xAA 0xC8 0x0F 0xC8 0xEF 0xBB

TEXT PROTOCOL

*:PxxxHyyyRzzz:#

Example
*:P200H020R100:#
Period:  20.0 ms
HIGH:     2.0 ms
Repeat: 100 times

 */
