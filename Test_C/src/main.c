/*
 ============================================================================
 Name        : Test_C2.c
 Author      : Tomasz Jokiel
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/global_types.h"
#include "headers/util.h"
#include <string.h>

typedef struct{
    UCHAR  ucId;          // Frame id (integer in range 10-99)
    UCHAR  ucProtVer;     // Protocol version (integer in range 0-9)
    UINT   uiCrc16;       // CRC16  (16-bit value)
    UCHAR* pucData;       // pointer to data buffer
    UCHAR  ucDataLength;  // data length
}RF_FRAME;

RF_FRAME stDecodeFrame(UCHAR* pucRawFrameData, UCHAR ucLength);
UCHAR* ucEncodeFrame(RF_FRAME stFrame);

int main(void) {
    puts("Hello Cruel World");
    CHAR acText[] = "DupaBlada";

    RF_FRAME stFrame = {.ucId           = 11,
                        .ucProtVer      = 2,
                        .uiCrc16        = uiCRC16((UCHAR*)acText, strlen(acText)),
                        .pucData        = (UCHAR*)acText,
                        .ucDataLength   = strlen(acText)};

    UCHAR* pucFrame = ucEncodeFrame(stFrame);
    for(UCHAR i = 0; i < sizeof(stFrame) - sizeof(UCHAR*) + stFrame.ucDataLength; i++){
        printf("%d \t%c\n", pucFrame[i], pucFrame[i]);
    }

    puts("----------------------------------");

    RF_FRAME stFrame2 = stDecodeFrame(pucFrame, sizeof(stFrame) - sizeof(UCHAR*) + stFrame.ucDataLength);
    for(UCHAR i = 0; i < sizeof(stFrame2); i++){
        printf("%d \t%c\n", (((UCHAR*)&stFrame2)[i]), (((UCHAR*)&stFrame2)[i]) );
    }

    puts("**********************************");
    puts( (stFrame.ucDataLength == stFrame2.ucDataLength) ? "length OK" : "length NOK" );
    puts( (stFrame.ucId == stFrame2.ucId) ? "Id OK" : "id NOK" );
    puts( (stFrame.ucProtVer == stFrame2.ucProtVer) ? "ProtVer OK" : "ProtVer NOK" );
    puts( (stFrame.uiCrc16 == stFrame2.uiCrc16) ? "Crc OK" : "Crc NOK" );

    if(stFrame.ucDataLength == stFrame2.ucDataLength){
        for(UCHAR i = 0; i < stFrame.ucDataLength; i++){
            if(stFrame.pucData[i] != stFrame2.pucData[i]){
                printf( "Frame data NOK at position: %i, [%i][%c] != [%i][%c]",
                        i ,
                        stFrame.pucData[i],  stFrame.pucData[i],
                        stFrame2.pucData[i], stFrame2.pucData[i] );
            }else{
                printf("%c", stFrame.pucData[i]);
            }
        }
    }

    return EXIT_SUCCESS;
}
