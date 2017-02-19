#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "system.h"


#define MAX_NBR_OF_TASKS            20

// ****************** WORKF FLOW FLAGS *************************************
#define WFF_PENDING_TASK_IN_QUEUE   0b00000001
#define WFF_SKIP_NEXT_TASK          0b00000010

#define SET_WORK_FLOW_FLAG(flag)    {uiWorkFlowFlag |= flag;}
#define CLEAR_WORK_FLOW_FLAG(flag)  {uiWorkFlowFlag &= ~flag;}
#define CHECK_WORK_FLOW_FLAG(flag)  (uiWorkFlowFlag & flag)

static pf_task_t vGetPendingTask(void);

static uint8_t ucPipeHead    = 0;
static uint8_t ucPipeTail    = 0;
static uint8_t ucQueueCnt    = 0;
static uint8_t uiWorkFlowFlag = 0b00000000;
static pf_task_t apfTasks[MAX_NBR_OF_TASKS];


/**
* Task dispatcher
*/
void vDispathTask(void){
    if( CHECK_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE) ){
        pf_task_t pfNextTask = vGetPendingTask();
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

    for(uint8_t i = 0; i < MAX_NBR_OF_TASKS; i++){
        apfTasks[i] = (pf_task_t)NULL;
    }
}


/**
*  Get task from queue
* @return pointer to task function, or NULL if queue empty
*/
static pf_task_t vGetPendingTask(void){
    pf_task_t pfNextTask = (pf_task_t)NULL;

    if(ucPipeHead == ucPipeTail){                                               // return nothing if no task in queue
        return (pf_task_t)NULL;
    }

    pfNextTask = apfTasks[ucPipeHead];                                          // retrieve next task

    ucPipeHead++;                                                               // shift head pointer
    ucPipeHead = (ucPipeHead == MAX_NBR_OF_TASKS) ? 0 : ucPipeHead;             // loop if need


    if(ucPipeHead == ucPipeTail){
        CLEAR_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE);                        // No other pending tasks
    }

    if(ucQueueCnt > 0){
        ucQueueCnt--;                                                           // Decrement count of tasks in queue
    }

    return pfNextTask;
}


/**
*  Add new task to queue
* @param task - pointer to task function
* @return TRUE if success, FALSE otherwise - queue full
*/
bool vSetPendingTask(pf_task_t task){

    if(ucQueueCnt >= (MAX_NBR_OF_TASKS - 1)){                                   // Always one element in queue is empty
        return false;                                                           // Queue if full :(
    }

    apfTasks[ucPipeTail] = task;
    SET_WORK_FLOW_FLAG(WFF_PENDING_TASK_IN_QUEUE);

    ucPipeTail++;                                                               // shift head pointer
    ucPipeTail = (ucPipeTail == MAX_NBR_OF_TASKS) ? 0 : ucPipeTail;


    if(ucQueueCnt < MAX_NBR_OF_TASKS){
        ucQueueCnt++;                                                           // Increment queue count
    }

    return true;
}
