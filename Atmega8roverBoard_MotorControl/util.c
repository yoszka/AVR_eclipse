/*
 * util.c
 *
 *  Created on: 24-01-2015
 *      Author: Tomasz Jokiel
 */

/**
 * Side effect - memory from pointer will be destroyed
 */
unsigned char ucGetThreeDigitValue(unsigned char * pBeginingMemoryToParse)
{
    pBeginingMemoryToParse[0] -= '0';
    pBeginingMemoryToParse[1] -= '0';
    pBeginingMemoryToParse[2] -= '0';

    return pBeginingMemoryToParse[0]*100 + pBeginingMemoryToParse[1]*10 + pBeginingMemoryToParse[2];
}
