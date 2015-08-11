/*
 * protocol.h
 *
 *      Author: Tomasz Jokiel
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "global_types.h"

#define DEBUG_OUTPUT FALSE

typedef BOOL(*T_PROTOCOL_HANDLER_FUNCTION)(UCHAR ucInputByte);

/**
 * @return TRUE if handled, FALSE otherwise
 */
BOOL bHandleInput(T_PROTOCOL_HANDLER_FUNCTION bProtocolHandler, UCHAR ucInputByte);

/**
 * @return TRUE if handled, FALSE otherwise
 */
BOOL bServoManualHandler(UCHAR ucInputByte);

/**
 * @return TRUE if handled, FALSE otherwise
 */
BOOL bMotorManualHandler(UCHAR ucInputByte);

#endif // PROTOCOL_H
