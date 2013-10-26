/*  task.h
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef INCLUDE_TASK
#define INCLUDE_TASK

#define MAX_NBR_OF_TASKS            (20)

// ****************** WORKF FLOW FLAGS *************************************
#define WFF_PENDING_TASK_IN_QUEUE   0b00000001
#define WFF_SKIP_NEXT_TASK          0b00000010

#define SET_WORK_FLOW_FLAG(flag)    {uiWorkFlowFlag |= flag;}
#define CLEAR_WORK_FLOW_FLAG(flag)  {uiWorkFlowFlag &= ~flag;}
#define CHECK_WORK_FLOW_FLAG(flag)  (uiWorkFlowFlag & flag)

// ******************** Typedefs *******************************************
typedef void(*T_TASK_FUNCTION)(void);

// ******************** Function declaration *******************************
void            vDispathTask    (void);
void            vInitPipe       (void);
T_TASK_FUNCTION vGetPendingTask (void);
BOOL            vSetPendingTask (T_TASK_FUNCTION task);

// tasks
void vTask_Delay1s                    (void);
void vTask_TurnOnLed1                 (void);
void vTask_TurnOnLed2                 (void);
void vTask_TurnOnLed3                 (void);
void vTask_TurnOffLed1                (void);
void vTask_TurnOffLed2                (void);
void vTask_TurnOffLed3                (void);
void vTask_WaitForSwitch1             (void);
void vTask_TramssmitAfterButtonPush   (void);

// ******************** External definition ********************************
extern T_TASK_FUNCTION  apfTasks[];
extern UINT             uiWorkFlowFlag;

#endif // INCLUDE_TASK
