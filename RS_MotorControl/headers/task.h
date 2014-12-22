#ifndef INCLUDE_TASK
#define INCLUDE_TASK

#include "global_types.h"

#define MAX_NBR_OF_TASKS            20

// ****************** WORKF FLOW FLAGS *************************************
#define WFF_PENDING_TASK_IN_QUEUE    0b00000001
#define WFF_SKIP_NEXT_TASK           0b00000010

#define SET_WORK_FLOW_FLAG(flag)    {uiWorkFlowFlag |= flag;}
#define CLEAR_WORK_FLOW_FLAG(flag)  {uiWorkFlowFlag &= ~flag;}
#define CHECK_WORK_FLOW_FLAG(flag)  (uiWorkFlowFlag & flag)

// ******************** Typedefs *******************************************
typedef void(*T_TASK_FUNCTION)(void);

// ******************** Function declaration *******************************
void             vDispathTask    (void);
void             vInitPipe       (void);
T_TASK_FUNCTION  vGetPendingTask (void);
BOOL             vSetPendingTask (T_TASK_FUNCTION task);

// tasks
void vDelay1s       (void);
void vTurnOnLed1    (void);
void vTurnOnLed2    (void);
void vTurnOnLed3    (void);
void vTurnOffLed1   (void);
void vTurnOffLed2   (void);
void vTurnOffLed3   (void);
void vServoP        (void);
void vServoS        (void);
void vServoL        (void);
void vServoManual   (void);
void vMotorManual   (void);

// ******************** External definition ********************************
extern T_TASK_FUNCTION  apfTasks[];
extern UINT             uiWorkFlowFlag;

#endif // INCLUDE_TASK
