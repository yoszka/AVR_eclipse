#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <util/delay.h>

#include "hardware.h"
#include "system.h"
#include "app_timer.h"
#include "gpio_int.h"

#define POMP_ENABLE_TIME_MS    (180000L)

#define POMP_OUT_PORT          PORTA
#define POMP_OUT_DDR           DDRA
#define POMP_OUT_BIT           2

#define POMP_OUT_ON()            {POMP_OUT_DDR |=  _BV(POMP_OUT_BIT);  POMP_OUT_PORT &= ~_BV(POMP_OUT_BIT);}  // NEGATIVE POLARISATION
#define POMP_OUT_OFF()           {POMP_OUT_DDR &= ~_BV(POMP_OUT_BIT);  POMP_OUT_PORT |=  _BV(POMP_OUT_BIT);}  // NEGATIVE POLARISATION

APP_TIMER_DEF(m_one_second_timer);

void buzz(void)
{
    for(int i = 0; i < 1000; i++)
    {
        BUZZ_ON(1);
        BUZZ_OFF(2);
        _delay_ms(1);
        BUZZ_ON(2);
        BUZZ_OFF(1)
    }
}

void gpio_handler(void)
{
    LED_ON(2);
    POMP_OUT_ON();
    app_timer_start(m_one_second_timer, POMP_ENABLE_TIME_MS);
    buzz();
}

void timeout_handler(void)
{
    LED_OFF(2);
    POMP_OUT_OFF();
}


int main (void)
{
    vInitPipe();
    gpio_int_init(gpio_handler);
    app_timer_init();

    app_timer_create(m_one_second_timer, APP_TIMER_MODE_SINGLE_SHOT, timeout_handler);

    while(true){
        vDispathTask();
    }

}

//******************************************************************************
//******************************************************************************

