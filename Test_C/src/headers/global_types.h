/*
 * global_types.h
 *
 *  Definition of the types
 *
 *  Created on: 04-12-2012
 *      Author: Tomasz Jokiel
 */

#ifndef GLOBAL_TYPES_H_
#define GLOBAL_TYPES_H_

#define TRUE            (!0)
#define FALSE           (0)

//#define NULL                  ((void*)0)

typedef int                     INT;
typedef unsigned int            UINT;
typedef char                    CHAR;
typedef unsigned char           UCHAR;
typedef unsigned char           BOOL;

typedef volatile int            VINT;
typedef volatile unsigned int   VUINT;
typedef volatile char           VCHAR;
typedef volatile unsigned char  VUCHAR;
typedef volatile unsigned char  VBOOL;

typedef volatile double         VDOUBLE;

#endif /* GLOBAL_TYPES_H_ */
