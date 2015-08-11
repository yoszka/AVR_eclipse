/*
 * adc.h
 *
 *  Created on: 22-01-2014
 *      Author: Tomasz Jokiel
 */

#ifndef INCLUDE_ADC_H
#define INCLUDE_ADC_H

#include "global_types.h"

void ADC_Init();
void ADC_Start();
void ADC_Stop();
void ADC_Enable();
void ADC_Disable();
UCHAR ADC_get8bitValue();

#endif // INCLUDE_ADC_H
