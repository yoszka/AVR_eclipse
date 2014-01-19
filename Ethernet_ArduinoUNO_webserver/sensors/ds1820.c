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


#include "ds1820.h"
#include "../timeout.h"


uint8_t therm_ds1820_reset()
{
	uint8_t i;
	//Pull line low and wait for 480uS
	THERM_DS1820_LOW();
	THERM_DS1820_OUTPUT_MODE();
	//fcpu_delay_us(430);	//480 //this must be smaller when moving delay func to other .c file
	_delay_us(430);
	//Release line and wait for 60uS
	THERM_DS1820_INPUT_MODE();
	_delay_us(60);
	//Store line value and wait until the completion of 480uS period
	i=(THERM_DS1820_PIN & (1<<THERM_DS1820_DQ));
	_delay_us(420);
	//Return the value read from the presence pulse (0=OK, 1=WRONG)
	return i;
}

void therm_ds1820_write_bit(uint8_t bit)
{
	//Pull line low for 1uS
	THERM_DS1820_LOW();
	THERM_DS1820_OUTPUT_MODE();
	_delay_us(1);
	//If we want to write 1, release the line (if not will keep low)
	if(bit) THERM_DS1820_INPUT_MODE();
	//Wait for 60uS and release the line
	_delay_us(50);
	THERM_DS1820_INPUT_MODE();
}

uint8_t therm_ds1820_read_bit(void)
{
	uint8_t bit=0;
	//Pull line low for 1uS
	THERM_DS1820_LOW();
	THERM_DS1820_OUTPUT_MODE();
	_delay_us(3);
	//Release line and wait for 14uS
	THERM_DS1820_INPUT_MODE();
	_delay_us(10);
	//Read line value
	if(THERM_DS1820_PIN&(1<<THERM_DS1820_DQ)) bit=1;
	//Wait for 45uS to end and return read value
	_delay_us(53);
	return bit;
}

uint8_t therm_ds1820_read_byte(void)
{
	uint8_t i=8, n=0;
	while(i--) {
		//Shift one position right and store read value
		n>>=1;
		n|=(therm_ds1820_read_bit()<<7);
	}
	return n;
}

uint16_t therm_ds1820_read_word(void)
{
	uint16_t i=16, n=0;
	while(i--) {
		//Shift one position right and store read value
		n>>=1;
		n|=(therm_ds1820_read_bit()<<15);
	}
	return n;
}

void therm_ds1820_write_byte(uint8_t byte)
{
	uint8_t i=8;
	while(i--) {
		//Write actual bit and shift one position right to make the next bit ready
		therm_ds1820_write_bit(byte&1);
		byte>>=1;
	}
}


int therm_ds1820_read_temperature()
{
	//Reset, skip ROM and start temperature conversion
	therm_ds1820_reset();
	therm_ds1820_write_byte(THERM_DS1820_CMD_SKIPROM);
	therm_ds1820_write_byte(THERM_DS1820_CMD_CONVERTTEMP);
	
	//Wait until conversion is complete
	while(!therm_ds1820_read_bit());
	
	//Reset, skip ROM and send command to read Scratchpad
	therm_ds1820_reset();
	therm_ds1820_write_byte(THERM_DS1820_CMD_SKIPROM);
	therm_ds1820_write_byte(THERM_DS1820_CMD_RSCRATCHPAD);
	uint8_t l = therm_ds1820_read_byte();
	uint8_t h = therm_ds1820_read_byte();
	therm_ds1820_reset();
	float temp = ( (h << 8) + l ) * 0.5;
	return (int)temp;
	/*
	  case TEMP_12_BIT:
	  return (float)rawTemperature * 0.0625;
	  break;
	  case TEMP_11_BIT:
	  return (float)(rawTemperature >> 1) * 0.125;
	  break;
	  case TEMP_10_BIT:
	  return (float)(rawTemperature >> 2) * 0.25;
	  break;
	  case TEMP_9_BIT:
	  return (float)(rawTemperature >> 3) * 0.5;
*/
}																																																																																