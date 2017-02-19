/*
 * usart.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */
#include <avr/io.h>


/**
 * Initialize USART
 */
void USART_Init( unsigned int baud )
{
    /* Set baud rate */
    UBRRH = (F_CPU/(baud*16L)-1) >> 8;                                          // Calculate register content to gain proper transmission speed
    UBRRL = (unsigned char)(F_CPU/(baud*16L)-1);
    /* Enable Interrupts on receive, Enable Receiver and Transmitter */
    UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, 1stop bit */
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);                                   //|(1<<USBS); //<- USBS in state 1 mean 2 bits stop, UMSEL=0 asynchronous transmission
}

/**
 * Transmit single byte
 */
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) );
    /* Put data into buffer, sends the data */
    UDR = data;
}

/**
 * Receive single byte
 */
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) );
    /* Get and return received data from buffer */
    return UDR;
}


/**
 * Transmit string
 * Precondition: String have to be zero terminated
 */
void USART_Transmit_string( unsigned char* string )
{
    while(*string)
    {
        USART_Transmit(*string++);
        //string++;
    }
}
