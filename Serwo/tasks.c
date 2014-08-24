#include "global_types.h"
#include "task.h"
#include "tasks_aux.h"
#include <util/delay.h>
#include "hardware.h"

/**
* Delay 1s
*/
void vDelay1s(void){
	for(int i = 0; i < 100; i++){
		_delay_ms(10);
	}
}


void vTurnOnLed1(void){
	LED_1_ON
}

void vTurnOffLed1(void){
	LED_1_OFF
}

void vTurnOnLed2(void){
	LED_2_ON
}

void vTurnOffLed2(void){
	LED_2_OFF
}

void vTurnOnLed3(void){
	LED_3_ON
}

void vTurnOffLed3(void){
	LED_3_OFF
}

void vServoP(void){

	for (int i = 0; i < 8; i++){
		LED_1_ON
		_delay_ms(0.2);
		LED_1_OFF
		_delay_ms(20.0);
	}
}


void vServoS(void){

	for (int i = 0; i < 13; i++){
		LED_1_ON
		_delay_ms(1.9);
		LED_1_OFF
		_delay_ms(20.0);
	}
}


void vServoL(void){

	for (int i = 0; i < 8; i++){
		LED_1_ON
		_delay_ms(2.5);
		LED_1_OFF
		_delay_ms(20.0);
	}
}

void vServoManual(void){

	for (int i = 0; i < g_stServoMenualParameters.uiRepeater; i++){
		LED_1_ON
		_delay_ms(g_stServoMenualParameters.dHigh);
//		_delay_us(dHigh);
		LED_1_OFF
		_delay_ms(g_stServoMenualParameters.dPeriod);
	}
}
