/*
 * app_timer.h
 *
 *  Created on: 18-02-2017
 *      Author: Tomasz Jokiel
 */

#ifndef APP_TIMER_H_
#define APP_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include "system.h"

typedef enum
{
    APP_TIMER_MODE_SINGLE_SHOT,
    APP_TIMER_MODE_REPEATED
} app_timer_mode_t;

typedef pf_task_t app_timer_timeout_handler_t;

typedef struct
{
    uint32_t                    ticks_to_expire;
    uint32_t                    ticks_already_counted;
    bool                        is_running;
    app_timer_mode_t            mode;
    app_timer_timeout_handler_t p_timeout_handler;
} app_timer_t;

typedef app_timer_t* app_timer_id_t;


#define APP_TIMER_DEF(timer_id)                                \
    static app_timer_t timer_id##_data = {0};                  \
    static const app_timer_id_t timer_id = &timer_id##_data


void app_timer_init(void);
bool app_timer_create(app_timer_id_t timer_id, app_timer_mode_t mode, app_timer_timeout_handler_t timeout_handler);
bool app_timer_start(app_timer_id_t timer_id, uint32_t timeout_ticks);
bool app_timer_stop(app_timer_id_t timer_id);


#endif /* APP_TIMER_H_ */
