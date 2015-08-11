/*
 * system.c
 *
 *      Author: Tomasz Jokiel
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "headers/global_types.h"
#include "headers/task.h"


// ****************** Global variables ******************************************************
static UCHAR ucPipeHead    = 0;
static UCHAR ucPipeTail    = 0;
static UCHAR ucQueueCnt    = 0;

// ******************************************************************************************
// ******************************************************************************************
// ******************************************************************************************
// ******************************************************************************************
// ******************************************************************************************

/**
 * Task dispatcher
 */
void vDispathTask(void){
    if( CHECK_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE) ){
        T_TASK_FUNCTION pfNextTask = vGetPendingTask();
        if(pfNextTask != NULL){
            pfNextTask();
        }
    }

}


/**
 *  Initialize pipe
 */
void vInitPipe(void){
    ucPipeHead = 0;
    ucPipeTail = 0;
    ucQueueCnt = 0;

    for(UCHAR i = 0; i < MAX_NBR_OF_TASKS; i++){
        apfTasks[i] = (T_TASK_FUNCTION)NULL;
    }
}


/**
 *  Get task from queue
 * @return pointer to task function, or NULL if queue empty
 */
T_TASK_FUNCTION vGetPendingTask(void){
    T_TASK_FUNCTION pfNextTask = (T_TASK_FUNCTION)NULL;

    if(ucPipeHead == ucPipeTail){                                        // return nothing if no task in queue
        return (T_TASK_FUNCTION)NULL;
    }

    pfNextTask = apfTasks[ucPipeHead];                                    // retrieve next task

    ucPipeHead++;                                                        // shift head pointer
    ucPipeHead = (ucPipeHead == MAX_NBR_OF_TASKS) ? 0 : ucPipeHead;        // loop if need


    if(ucPipeHead == ucPipeTail){
        CLEAR_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE);                // No other pending tasks
    }

    if(ucQueueCnt > 0){
        ucQueueCnt--;                                                    // Decrement count of tasks in wueue
    }

    return pfNextTask;
}


/**
 *  Add new task to queue
 * @param task - pointer to task function
 * @return TRUE if success, FALSE otherwise - queue full
 */
BOOL vSetPendingTask(T_TASK_FUNCTION task){

    if(ucQueueCnt >= (MAX_NBR_OF_TASKS - 1)){                            // Always one element in queue is empty
        return FALSE;                                                    // Queue if full ;(
    }

    apfTasks[ucPipeTail] = task;
    SET_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE);

    ucPipeTail++;                                                        // shift head pointer
    ucPipeTail = (ucPipeTail == MAX_NBR_OF_TASKS) ? 0 : ucPipeTail;


    if(ucQueueCnt < MAX_NBR_OF_TASKS){
        ucQueueCnt++;                                                    // Increment queue count
    }

    return TRUE;
}
