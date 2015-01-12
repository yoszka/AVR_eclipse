#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "headers/global_types.h"
#include "headers/hardware.h"


// ****************** DEFINITION ***********************************************************


// ****************** Global variables ******************************************************
// *****************************************************************************************

INT main (void)
{

    LED_ON
    BOOL tst = TRUE;
//            MOTOR_2_ENA_HI
//            MOTOR_1_ENA_HI
    MOTOR_1_ENA_LOW
    MOTOR_2_ENA_LOW

    while(TRUE){
        _delay_ms(2000);
        LED_TOGGLE

        if(tst)
        {
            MOTOR_1_DIR_LEFT
            MOTOR_2_DIR_LEFT
        }
        else
        {
            MOTOR_1_DIR_RIGHT
//            MOTOR_1_ENA_LOW
            MOTOR_2_DIR_RIGHT
//            MOTOR_2_ENA_LOW
        }
        tst = !tst;
    }

}

//******************************************************************************
//******************************************************************************

