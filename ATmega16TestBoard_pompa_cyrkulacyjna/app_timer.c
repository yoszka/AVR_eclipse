/*
 * app_timer.c
 *
 *  Created on: 18-02-2017
 *      Author: Tomasz Jokiel
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "system.h"
#include "app_timer.h"

#define TIMERS_COUNT_MAX        10

static void hw_timer_0_init(void);

static app_timer_id_t m_app_timers_arr[TIMERS_COUNT_MAX] = {0};
static uint_fast8_t m_timers_cnt = 0;

void app_timer_init(void)
{
    hw_timer_0_init();
    m_timers_cnt = 0;
    memset(m_app_timers_arr, 0x00, sizeof(m_app_timers_arr));
}

static void hw_timer_0_init(void)
{
    TCNT0 = 0;                                  // reset counter value
    OCR0  = 125;                                //compare when reach 100
    TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00); // compare with OCR0 mode, prescaler 64
    TIMSK = (1<<OCIE0) | (1<<TOIE0);            // unlock interrupt from compare and overflow
    sei();
}

ISR(TIMER0_COMP_vect) {

    for(int i = 0; i < m_timers_cnt; i++)
    {
        if(m_app_timers_arr[i] != NULL && m_app_timers_arr[i]->is_running)
        {
            m_app_timers_arr[i]->ticks_already_counted++;

            if(m_app_timers_arr[i]->ticks_already_counted == m_app_timers_arr[i]->ticks_to_expire)
            {
                m_app_timers_arr[i]->ticks_already_counted = 0;
                vSetPendingTask(m_app_timers_arr[i]->p_timeout_handler);

                if(m_app_timers_arr[i]->mode == APP_TIMER_MODE_SINGLE_SHOT)
                {
                    m_app_timers_arr[i]->is_running = false;
                }
            }
        }
    }
}



bool app_timer_create(app_timer_id_t timer_id, app_timer_mode_t mode, app_timer_timeout_handler_t timeout_handler)
{
    if (timeout_handler == NULL     ||
            timer_id == NULL      ||
            timer_id->is_running ||
            m_timers_cnt == TIMERS_COUNT_MAX)
    {
        return false;
    }

    timer_id->mode = mode;
    timer_id->p_timeout_handler = timeout_handler;

    m_app_timers_arr[m_timers_cnt++] = timer_id;

    return true;
}

bool app_timer_start(app_timer_id_t timer_id, uint32_t timeout_ticks)
{
    if (timer_id->p_timeout_handler == NULL)
    {
        return false;
    }

    timer_id->ticks_already_counted = 0;
    timer_id->ticks_to_expire = timeout_ticks;
    timer_id->is_running = true;

    return true;
}

bool app_timer_stop(app_timer_id_t timer_id)
{
    timer_id->is_running = false;
    return true;
}

