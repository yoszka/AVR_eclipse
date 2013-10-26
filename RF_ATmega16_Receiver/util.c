/*
 * util.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#include "headers/global_types.h"
#include "headers/util.h"

/**
 * @param pucInputData pointer to input data - zero terminated string
 * @return CRC16 value of the input data
 */
UINT CRC16(UCHAR* pucInputData)
{
    UINT uiCRC16n = 0xFFFF;
    UINT uiTmp;

    for(UCHAR k = 0; k < 5; k++)                                                //TODO Why magic 5
    {
        if(*pucInputData == 0){
            *pucInputData = ZERO_SIGN;                                          // Replace with ZERO_SIGN
        }
        uiTmp = (UINT) *pucInputData++;
        uiCRC16n ^= uiTmp;
        for(UCHAR i=0; i < 8; i++){                                             // Suppose magic 8 is bit counts
            uiCRC16n >>= 1;
            if(uiCRC16n & 0x01){
                uiCRC16n ^= 0xA001;                                             // EXOR if first bit is 1
            }
        }
    }

    *pucInputData++ = (UCHAR) uiCRC16n;                                         // LSB of CRC16
    *pucInputData   = uiCRC16n >>8;                                             // MSB of CRC16
    return uiCRC16n;
}
