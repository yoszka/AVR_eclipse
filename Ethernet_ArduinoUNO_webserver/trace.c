/*
 * trace.c
 *
 *  Created on: 30-01-2014
 *      Author: Tomasz Jokiel
 */

#include "usart.h"
#include <stdarg.h>
#include <stdio.h>

void initTrace(void) {
    static unsigned char isInitialized = 0;
    if(!isInitialized) {
        USART_Init ( USART_BAUD_RATE );
    }
}

void trace(const char* message) {
    USART_Transmit_string((unsigned char*)message);
}

//void trace(const char* format, ...) {
//    char buffer[100] = {0};
//    va_list ap;
//    va_start(ap, format);
//    sprintf(buffer, format, ap);
//    USART_Transmit_string((unsigned char*)buffer);
//    va_end(ap);
//}
