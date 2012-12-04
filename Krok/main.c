#include <avr/io.h>
#include <util/delay.h>
#include "global_types.h"
#include "header_file_1.h"
#include "header_file_2.h"
#include "task.h"
#include "hardware.h"


// ****************** DEFINITION ***********************************************************



// ****************** Global variables ******************************************************
UINT uiWorkFlowFlag = 0b00000000;
T_TASK_FUNCTION apfTasks[MAX_NBR_OF_TASKS];

// *****************************************************************************************

INT main (void)
{
	LED_1_ON
	LED_2_ON
	LED_3_ON

	vInitPipe();
	
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vTurnOffLed2);
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vTurnOffLed3);

	vSetPendingTask(vDelay1s);
	vSetPendingTask(vTurnOnLed1);
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vTurnOnLed2);
	vSetPendingTask(vDelay1s);
	vSetPendingTask(vTurnOnLed3);

  while(TRUE){
	  vDispathTask();
  }

}

//***************************************************************************************************
//***************************************************************************************************
