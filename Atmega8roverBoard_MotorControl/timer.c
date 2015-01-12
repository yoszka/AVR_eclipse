#include <avr/io.h>
#include <avr/interrupt.h>
#include "headers/global_types.h"
#include "headers/hardware.h"
#include "headers/motor.h"
#include "headers/timer.h"

#define ONE_SECOND_TIMER_0_VAL    31
#define FULL_PWM_TIMER1_PERIOD   255

volatile uint8_t uiSoftCounterTimer0 = 0;
volatile uint8_t g_ucSoftPWMTimer1Hign = 128;
volatile uint8_t g_ucSoftPWMTimer1Low  = 127;
volatile uint8_t g_ucSoftPWMTimer2High = 128;
volatile uint8_t g_ucSoftPWMTimer2Low  = 127;

void initTimer0(void)
{
    // prescaler F_CPU/1024
    TCCR0 |= (1<<CS00) | (1<<CS02);
    // interrupt from overflow
    TIMSK |= 1<<TOIE0;
    // start value
    TCNT0 = 1;
}

void resetTimer0(void)
{
    // set timer value
    TCNT0 = 1;
    uiSoftCounterTimer0 = 0;
}

ISR(TIMER0_OVF_vect)
{
    if(++uiSoftCounterTimer0 == ONE_SECOND_TIMER_0_VAL)
    {
        uiSoftCounterTimer0 = 0;
        // 1 second
        LED_TOGGLE

        vLeftMotorStop();
        vRightMotorStop();
    }
}

void initTimerMotorTimers(void)
{
    initTimer1A_CTC();
    initTimer2_CTC();
}

void initTimer1A_CTC(void)
{
    // Configure TIMER1: CTC mode, prescaler F_CPU/1024
    TCCR1A = 0;
    TCCR1B = (1<<WGM12) | (1<<CS00) | (1<<CS02);

    // TIMER1A compare value
    setTimer1A_CTC_value(0x0010);
//    OCR1AH = 0x00;
//    OCR1AL = 0x40;

    // TIMER1B compare value [cannot use both channels in one time - they affect each other, using same counter]
    //OCR1BH = 0x00;
    //OCR1BL = 0x1F;

    // interrupt from overflow [cannot use both channels in one time - they affect each other, using same counter]
//    TIMSK |= (1<<OCIE1A) | (1<<OCIE1B);
    TIMSK |= (1<<OCIE1A);
    // start value
    TCNT1H = 0;
    TCNT1L = 0;
}

void setTimer1A_CTC_value(uint16_t uiValueToCompare)
{
    OCR1AH = (uint8_t)(uiValueToCompare>>8);
    OCR1AL = (uint8_t)uiValueToCompare;
}

uint16_t getTimer1A_CTC_value(void)
{
    uint16_t uiRetVal = 0;

    uiRetVal  = OCR1AH<<8;
    uiRetVal += OCR1AL;

    return uiRetVal;
}

void setSoftPWMvalueTimer1(uint8_t ucValuePWm)
{
    g_ucSoftPWMTimer1Hign = ucValuePWm;
    g_ucSoftPWMTimer1Low  = FULL_PWM_TIMER1_PERIOD - g_ucSoftPWMTimer1Hign;
}

void vHandleLeftMotorSpeed() {
    const uint16_t uiTimer1A_CTC_value = getTimer1A_CTC_value();

    if ((uint8_t) uiTimer1A_CTC_value == g_ucSoftPWMTimer1Hign) {
        MOTOR_1_ENA_LOW
        setTimer1A_CTC_value(g_ucSoftPWMTimer1Low);
    } else if(0 == g_ucSoftPWMTimer1Hign){
        MOTOR_1_ENA_LOW;
    } else {
        MOTOR_1_ENA_HI
        setTimer1A_CTC_value(g_ucSoftPWMTimer1Hign);
    }
}

ISR(TIMER1_COMPA_vect)
{
    vHandleLeftMotorSpeed();
    TIFR |= (1<<OCF1A);
    TCNT1H = 0;
    TCNT1L = 0;
}

//ISR(TIMER1_COMPB_vect)
//{
//    //
//}

void initTimer2_CTC(void)
{
    TCCR2 = (1<<WGM21) | (1<<CS22) | (1<<CS21) | (1<<CS20);
    TIMSK |= (1<<OCIE2);
    OCR2 = 127;
    TCNT2 = 0x00;
}

void vHandleRightMotorSpeed() {
    const uint8_t ucTimer2_CTC_value = getTimer2_CTC_value();

    if ((uint8_t) ucTimer2_CTC_value == g_ucSoftPWMTimer2High) {
        MOTOR_2_ENA_LOW
        setTimer2_CTC_value(g_ucSoftPWMTimer2Low);
    } else if(0 == g_ucSoftPWMTimer2High){
        MOTOR_2_ENA_LOW;
    } else {
        MOTOR_2_ENA_HI
        setTimer2_CTC_value(g_ucSoftPWMTimer2High);
    }
}

uint8_t getTimer2_CTC_value(void)
{
    return OCR2;
}

void setTimer2_CTC_value(uint8_t ucValueToCompare)
{
    OCR2 = ucValueToCompare;
}

void setSoftPWMvalueTimer2(uint8_t ucValuePWm)
{
    g_ucSoftPWMTimer2High = ucValuePWm;
    g_ucSoftPWMTimer2Low  = FULL_PWM_TIMER1_PERIOD - g_ucSoftPWMTimer2High;
}

ISR(TIMER2_COMP_vect)
{
    vHandleRightMotorSpeed();
    TIFR |= (1<<OCF2);
    TCNT2 = 0x00;
}
