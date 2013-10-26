/*
 * usart.h
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef USART_H_
#define USART_H_

//#define BAUD 	9600
//#define MYUBRR 	F_CPU/16/BAUD-1

#define USART_BAUD_RATE                 (1200)

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Transmit_string( unsigned char* string );

#endif /* USART_H_ */
