#include "global_types.h"
#include "task.h"
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
