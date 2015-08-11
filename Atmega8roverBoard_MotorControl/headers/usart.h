/*
 * usart.h
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef USART_H_
#define USART_H_

void USART_Init( UINT baud );
void USART_Transmit( UCHAR data );
UCHAR USART_Receive( void );
void USART_Transmit_string( UCHAR* string );

#endif /* USART_H_ */
