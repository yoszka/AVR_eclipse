/*
 * gpio_int.h
 *
 *  Created on: 18-02-2017
 *      Author: Tomasz Jokiel
 */

#ifndef GPIO_INT_H_
#define GPIO_INT_H_

#include "system.h"

typedef pf_task_t pf_gpio_int_handler_t;

void gpio_int_init(pf_gpio_int_handler_t gpio_int_handler);

#endif /* GPIO_INT_H_ */
