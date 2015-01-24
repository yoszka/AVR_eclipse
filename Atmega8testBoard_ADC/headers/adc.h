/*
 * adc.h
 *
 *  Created on: 22-01-2014
 *      Author: Tomasz Jokiel
 */

#ifndef INCLUDE_ADC_H
#define INCLUDE_ADC_H

void ADC_Init();
void ADC_Start();
void ADC_Stop();
void ADC_Enable();
void ADC_Disable();
unsigned char ADC_get8bitValue();

#endif // INCLUDE_ADC_H
