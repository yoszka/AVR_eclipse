/*
 * usart.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#include <avr/io.h>

#if ! (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
    #error "This file include registers for ATmega328P or AVR_ATmega328, comment this and check errors."
#endif
/**
 * Initialize USART
 */
void USART_Init( unsigned int baud )
{
    /* Set baud rate */
    UBRR0H = (F_CPU/(baud*16L)-1) >> 8;                                          // Calculate register content to gain proper transmission speed
    UBRR0L = (unsigned char)(F_CPU/(baud*16L)-1);
    /* Enable Interrupts on receive, Enable Receiver and Transmitter */
    UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    //UCSR0C = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);                                   //|(1<<USBS); //<- USBS in state 1 mean 2 bits stop, UMSEL=0 asynchronous transmission
}

/**
 * Transmit single byte
 */
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

/**
 * Receive single byte
 */
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
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
