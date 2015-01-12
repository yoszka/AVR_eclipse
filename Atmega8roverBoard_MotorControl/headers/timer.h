/*
 * timer.h
 *
 *  Created on: 24-08-2014
 *      Author: Tomasz Jokiel
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void initTimer0(void);
void resetTimer0(void);
void initTimer1A_CTC(void);
void setTimer1A_CTC_value(uint16_t uiValueToCompare);
uint16_t getTimer1A_CTC_value(void);
void setSoftPWMvalueTimer1(uint8_t ucValuePWm);
void initTimer2_CTC(void);
uint8_t getTimer2_CTC_value(void);
void setTimer2_CTC_value(uint8_t ucValueToCompare);
void initTimerMotorTimers(void);
void setSoftPWMvalueTimer2(uint8_t ucValuePWm);

#endif /* TIMER_H_ */
