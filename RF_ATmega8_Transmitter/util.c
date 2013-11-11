/*
 * util.c
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#include "headers/global_types.h"
#include "headers/util.h"
//#include <string.h>

/**
 * @param pucInputData pointer to input data
 * @return CRC16 value of the input data
 */
UINT uiCRC16(UCHAR* pucInputData, UCHAR ucLength)
{
    UINT uiCRC16n = 0xFFFF;
    UINT uiTmp;

    for(UCHAR k = 0; k < ucLength; k++)
    {
        if(*pucInputData == 0){
            uiTmp = (UINT) ZERO_SIGN;
        }else{
            uiTmp = (UINT) *pucInputData++;
        }
        uiCRC16n ^= uiTmp;
        for(UCHAR i = 0; i < 8; i++){                                           // Suppose magic 8 is bit counts
            uiCRC16n >>= 1;
            if(uiCRC16n & 0x0001){
                uiCRC16n ^= 0xA001;                                             // EXOR if first bit is 1
            }
        }
    }

//    *pucInputData++ = (UCHAR) uiCRC16n;                                         // LSB of CRC16
//    *pucInputData   = uiCRC16n >> 8;                                            // MSB of CRC16
    return uiCRC16n;
}
