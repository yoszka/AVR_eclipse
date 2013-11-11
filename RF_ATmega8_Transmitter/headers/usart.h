/*
 * usart.h
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef USART_H_
#define USART_H_

#define USART_BAUD_RATE                 (1200)

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Transmit_string( unsigned char* string );
void USART_Transmit_buffer(unsigned char* buffer, unsigned char length);

#endif /* USART_H_ */
