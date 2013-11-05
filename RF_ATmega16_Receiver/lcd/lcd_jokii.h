/*
 * lcd_jokii.h
 *
 * Header file for controling LCD display with HD44780 driver
 * 4-bit mode, without reading busy flag
 * Chip : Atmel ATmega
 * Compilator : avr-gcc
 *
 * Functions "LCD_ZapiszText" and "LCD_XY" construct at pattern of
 * Rados³awa Kwiecieñ: "HD44780.c"
 *
 *  Created on: 30.07.2009
 *      Author: Tomasz Jokiel
 */

#ifndef LCD_JOKII_H_
#define LCD_JOKII_H_

#include <avr/io.h>

// Ports definition
#define LCD_REJ_KIER_RS_E   DDRA
#define LCD_REJ_PORT_RS_E   PORTA
#define LCD_RS              2
#define LCD_E               3

#define LCD_REJ_KIER        DDRA
#define LCD_REJ_PORT        PORTA
#define LCD_DB4             4
#define LCD_DB5             5
#define LCD_DB6             6
#define LCD_DB7             7

// instructions
#define dane                1
#define instrukcja          0
#define LOWERLINE           LCD_XY(0,1);

// functions
void LCD_SEND       (unsigned char, unsigned char);
void LCD_Czysc      (void);
void LCD_Ini        (void);
void LCD_ZapiszText (char *);
void LCD_XY         (unsigned char , unsigned char);
void LCD_LICZBA     (unsigned int);
void POLSKIE_ZNAKI  (void);

#endif /* LCD_JOKII_H_ */
