/*
 * system.h
 *
 *  Created on: 18-02-2017
 *      Author: Tomasz Jokiel
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdbool.h>

typedef void(*pf_task_t)(void);

void vInitPipe(void);
void vDispathTask(void);
bool vSetPendingTask(pf_task_t task);

#endif /* SYSTEM_H_ */
