/*
 * Copyright (C) 2012, Radu Motisan , radu.motisan@gmail.com
 *
 * http://www.pocketmagic.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * 
 * @purpose DS1820 Temperature Sensor Minimal interface for Atmega microcontrollers
 * http://www.pocketmagic.net/
 */

/*********************************************
 * CONFIGURE THE WORKING PIN
 *********************************************/

#pragma once

#include <avr/io.h> 
#include <stdio.h>

#define THERM_DS1820_PORT PORTC
#define THERM_DS1820_DDR DDRC
#define THERM_DS1820_PIN PINC
#define THERM_DS1820_DQ PC2
/* Utils */
#define THERM_DS1820_INPUT_MODE() THERM_DS1820_DDR&=~(1<<THERM_DS1820_DQ)
#define THERM_DS1820_OUTPUT_MODE() THERM_DS1820_DDR|=(1<<THERM_DS1820_DQ)
#define THERM_DS1820_LOW() THERM_DS1820_PORT&=~(1<<THERM_DS1820_DQ)
#define THERM_DS1820_HIGH() THERM_DS1820_PORT|=(1<<THERM_DS1820_DQ)
/* list of these commands translated into C defines:*/
#define THERM_DS1820_CMD_CONVERTTEMP 0x44
#define THERM_DS1820_CMD_RSCRATCHPAD 0xbe
#define THERM_DS1820_CMD_WSCRATCHPAD 0x4e
#define THERM_DS1820_CMD_CPYSCRATCHPAD 0x48
#define THERM_DS1820_CMD_RECEEPROM 0xb8
#define THERM_DS1820_CMD_RPWRSUPPLY 0xb4
#define THERM_DS1820_CMD_SEARCHROM 0xf0
#define THERM_DS1820_CMD_READROM 0x33
#define THERM_DS1820_CMD_MATCHROM 0x55
#define THERM_DS1820_CMD_SKIPROM 0xcc
#define THERM_DS1820_CMD_ALARMSEARCH 0xec
/* constants */
#define THERM_DS1820_DECIMAL_STEPS_12BIT 625 //.0625

void therm_ds1820_delay(uint16_t delay);
uint8_t therm_ds1820_reset();
void therm_ds1820_write_bit(uint8_t bit);
uint8_t therm_ds1820_read_bit(void);
uint8_t therm_ds1820_read_byte(void);
void therm_ds1820_write_byte(uint8_t byte);
//void therm_read_temperature(int *digi, int *deci);
int therm_ds1820_read_temperature();