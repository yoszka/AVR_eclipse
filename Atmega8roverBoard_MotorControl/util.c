/*
 * util.c
 *
 *  Created on: 24-01-2015
 *      Author: Tomasz Jokiel
 */

#include "headers/global_types.h"

/**
 * Side effect - memory from pointer will be destroyed
 */
UCHAR ucGetThreeDigitValue(UCHAR * pBeginingMemoryToParse)
{
    pBeginingMemoryToParse[0] -= '0';
    pBeginingMemoryToParse[1] -= '0';
    pBeginingMemoryToParse[2] -= '0';

    return pBeginingMemoryToParse[0]*100 + pBeginingMemoryToParse[1]*10 + pBeginingMemoryToParse[2];
}
