#include <avr/io.h>
#include <util/delay.h>
#include "global_types.h"
#include "hardware.h"
#include "usart.h"
#include <avr/interrupt.h>


// ****************** DEFINITION ***********************************************
#define RECEIVED_BYTE_BUFFER_SIZE		32


// ****************** Global variables *****************************************
volatile unsigned char dataReceived[RECEIVED_BYTE_BUFFER_SIZE];
volatile unsigned char startReading = 0;
volatile unsigned char lastByte = 0;
volatile unsigned int receivedByteCount = 0;

volatile double dPeriod 	= 0.0;
volatile double dHigh 		= 0.0;
volatile double uiRepeater 	= 0.0;

unsigned int temp = 0;
// *****************************************************************************

INT main (void)
{
	LED_1_ON
	LED_2_ON
	LED_3_ON

	USART_Init ( 9600 );
	sei();

	USART_Transmit_string((unsigned char*)"Probna transmisja\n");

//	USART_Transmit(USART_Receive());

//	USART_Transmit_string((unsigned char*)"TEST\n");
	while(1);
}

//******************************************************************************
//******************************************************************************
ISR(USART_RXC_vect)
{
	LED_1_TOGGLE
//	LED_1_OFF
	unsigned char byte = UDR;

    if((lastByte == '*') && (byte == ':') && (receivedByteCount == 0))                               //Detect Start frame
    {
      dataReceived[receivedByteCount++] = lastByte;
    }

    if(receivedByteCount > 0)
    {
    	dataReceived[receivedByteCount++] = byte;
    	if(receivedByteCount == RECEIVED_BYTE_BUFFER_SIZE) receivedByteCount--;
    }


    if((lastByte == ':') && (byte == '#') && (receivedByteCount > 10)){
    	dataReceived[receivedByteCount++] = 0x00;
    	USART_Transmit_string(dataReceived);
    	receivedByteCount = 0;

    	if(dataReceived[2] == 'P'){
    		USART_Transmit_string("Period = ");
    		USART_Transmit(dataReceived[3]);
    		USART_Transmit(dataReceived[4]);
    		USART_Transmit(dataReceived[5]);

    		dataReceived[3] -= '0';
    		dataReceived[4] -= '0';
    		dataReceived[5] -= '0';

    		temp = dataReceived[3]*100 + dataReceived[4]*10 + dataReceived[5];

    		dPeriod = ((double)temp)*0.1;
    	}
    	if(dataReceived[6] == 'H'){
    		USART_Transmit_string("HIGH = ");
    		USART_Transmit(dataReceived[7]);
    		USART_Transmit(dataReceived[8]);
    		USART_Transmit(dataReceived[9]);

    		dataReceived[7] -= '0';
    		dataReceived[8] -= '0';
    		dataReceived[9] -= '0';

    		temp = dataReceived[7]*100 + dataReceived[8]*10 + dataReceived[9];

    		dPeriod = ((double)temp)*0.1;
    	}
    	if(dataReceived[10] == 'R'){
    		USART_Transmit_string("Repeater = ");
    		USART_Transmit(dataReceived[11]);
    		USART_Transmit(dataReceived[12]);
    		USART_Transmit(dataReceived[13]);

    		dataReceived[11] -= '0';
    		dataReceived[12] -= '0';
    		dataReceived[13] -= '0';

    		uiRepeater = dataReceived[11]*100 + dataReceived[12]*10 + dataReceived[13];


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


 */
