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
 * @purpose DHT11 Humidity & Temperature Sensor
 *	DHT11
 *	20-90%RH ±5?RH
 *	0-50 ? ±2?
 *	4 Pin Single Row
 */

/*********************************************
 * CONFIGURE THE WORKING PIN
 *********************************************/

#pragma once

#include <avr/io.h> 
#include <stdio.h>

#define DHT11_PORT PORTC
#define DHT11_DDR DDRC
#define DHT11_PIN PINC
#define DHT11_DQ PC1
/* Utils */
#define DHT11_INPUT_MODE() DHT11_DDR&=~(1<<DHT11_DQ)
#define DHT11_OUTPUT_MODE() DHT11_DDR|=(1<<DHT11_DQ)
#define DHT11_LOW() DHT11_PORT&=~(1<<DHT11_DQ)
#define DHT11_HIGH() DHT11_PORT|=(1<<DHT11_DQ)

#define DHTLIB_OK                               0
#define DHTLIB_ERROR_CHECKSUM					-1
#define DHTLIB_ERROR_TIMEOUT					-2


int DHT11_read(int *temp, int *humidity);