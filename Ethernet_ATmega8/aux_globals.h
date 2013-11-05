/* @project 
 * 
 * License to access, copy or distribute this file.
 * This file or any portions of it, is Copyright (C) 2012, Radu Motisan ,  http://www.pocketmagic.net . All rights reserved.
 * @author Radu Motisan, radu.motisan@gmail.com
 * 
 * This file is protected by copyright law and international treaties. Unauthorized access, reproduction 
 * or distribution of this file or any portions of it may result in severe civil and criminal penalties.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * 
 * @purpose Eth interface for Atmega microcontrollers
 * http://www.pocketmagic.net/?p=2866
 */


#pragma once

#include <avr/io.h> 
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
//custom headsers
//#include "HD44780.h"

//delay functions
//#define F_CPU 8000000UL 		//Your clock speed in Hz (16Mhz here)

//-----------------delays---------------------------------------------------------
#define LOOP_CYCLES 8 				//Number of cycles that the loop takes

#define fcpu_delay_us(num) delay_int(num/(LOOP_CYCLES*(1/(F_CPU/1000000.0))))
#define fcpu_delay_ms(num) delay_int(num/(LOOP_CYCLES*(1/(F_CPU/1000.0))))

void delay_int(unsigned long delay);
//--------------------------------------------------------------------------------


#define PORT_ON( port_letter, number )			port_letter |= (1<<number)
#define PORT_OFF( port_letter, number )			port_letter &= ~(1<<number)
#define PORT_ALL_ON( port_letter, number )		port_letter |= (number)
#define PORT_ALL_OFF( port_letter, number )		port_letter &= ~(number)
#define FLIP_PORT( port_letter, number )		port_letter ^= (1<<number)
#define PORT_IS_ON( port_letter, number )		( port_letter & (1<<number) )
#define PORT_IS_OFF( port_letter, number )		!( port_letter & (1<<number) )
