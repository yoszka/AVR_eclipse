/*
 * lcd_jokii.c
 *
 * Library for controling LCD display with HD44780 driver
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

#include <util/delay.h>
#include "lcd_jokii.h"


void LCD_SEND(unsigned char command, unsigned char komenda_lub_instrukcja)
{

    if(komenda_lub_instrukcja) 	LCD_REJ_PORT_RS_E |= _BV(LCD_RS);               // linia RS w stanie wysokim - wys³ane dane bêd¹ danymi
    else LCD_REJ_PORT_RS_E &= ~_BV(LCD_RS);                                     // jeœli instrukcjami to RS w stan niski

    for(unsigned int k=0;k<2;k++)
    {
        LCD_REJ_PORT_RS_E |= _BV(LCD_E);                                        // linia Enable w stanie wysokim
        LCD_REJ_PORT &= ~_BV(LCD_DB4) & ~_BV(LCD_DB5) & ~_BV(LCD_DB6) & ~_BV(LCD_DB7); // linie danych wyzerowane
        if(command & 0b00010000) LCD_REJ_PORT |= _BV(LCD_DB4);
        if(command & 0b00100000) LCD_REJ_PORT |= _BV(LCD_DB5);
        if(command & 0b01000000) LCD_REJ_PORT |= _BV(LCD_DB6);
        if(command & 0b10000000) LCD_REJ_PORT |= _BV(LCD_DB7);
        LCD_REJ_PORT_RS_E &= ~_BV(LCD_E);                                       // opadaj¹ce zbocze Enable potwierdzaj¹ce dane DB4 .. DB7
        command <<= 4;                                                          // przesuniêcie o 4 bity w lewo zawatoœci command
    }

    //for(unsigned int i=0; i<5; i++) _delay_us(10);                            // opóŸnienie 50us
    _delay_us(50);

}

void LCD_Czysc(void)
{
    LCD_SEND(0b00000001, instrukcja);                                           // czyœæ LCD
    _delay_ms(2);                                                               // opóŸnienie po wyczyszczeniu wyœwietlacza
    LCD_SEND(0b00000010, instrukcja);                                           // powrót do HOME
    _delay_ms(2);
}


void LCD_Ini(void)
{
    LCD_REJ_KIER 		|= _BV(LCD_DB4) | _BV(LCD_DB5) | _BV(LCD_DB6) | _BV(LCD_DB7);   // porty wyœwietlacza pracuj¹ jako wyjœcie
    LCD_REJ_KIER_RS_E 	|= _BV(LCD_RS)  | _BV(LCD_E);                           // porty RS i E
    //LCD_REJ_PORT |= _BV(LCD_RS);                                              // wysy³ane dane bêd¹ instrukcjami
    LCD_REJ_PORT_RS_E &= ~_BV(LCD_RS);                                          // wysy³ane dane bêd¹ instrukcjami

    LCD_REJ_PORT_RS_E |= _BV(LCD_E);                                            // linia Enable w stanie wysokim
    //for(unsigned int i=0; i<5; i++) _delay_ms(10);                            // opóŸnienie 50ms od w³¹czenia zasilania
    _delay_us(50);

    LCD_REJ_PORT |= _BV(LCD_DB4) | _BV(LCD_DB5);                                // ustaw DB7-DB4 na 0011
    LCD_REJ_PORT &= ~_BV(LCD_DB6) & ~_BV(LCD_DB7);

    //_delay_us(1);
    LCD_REJ_PORT_RS_E &= ~_BV(LCD_E);                                           // opadaj¹ce zbocze Enable potwierdzaj¹ce dane DB4 .. DB7
    _delay_ms(5);                                                               // odczekaj 5ms

    LCD_REJ_PORT_RS_E |= _BV(LCD_E);                                            // linia Enable w stanie wysokim
    _delay_us(1);
    LCD_REJ_PORT_RS_E &= ~_BV(LCD_E);                                           // opadaj¹ce zbocze Enable potwierdzaj¹ce dane DB4 .. DB7
    _delay_us(100);
    //for(unsigned int i=0; i<10; i++) _delay_us(10);                           // opóŸnienie 100us


    LCD_REJ_PORT_RS_E |= _BV(LCD_E);                                            // linia Enable w stanie wysokim
    _delay_us(1);
    LCD_REJ_PORT_RS_E &= ~_BV(LCD_E);                                           // opadaj¹ce zbocze Enable potwierdzaj¹ce dane DB4 .. DB7
    _delay_us(100);
    //for(unsigned int i=0; i<10; i++) _delay_us(10);                           // opóŸnienie 100us


    LCD_REJ_PORT &= ~_BV(LCD_DB4);                                              // ustaw DB7-DB4 na 0010
    LCD_REJ_PORT_RS_E |= _BV(LCD_E);                                            // linia Enable w stanie wysokim
    //_delay_us(1);
    LCD_REJ_PORT_RS_E &= ~_BV(LCD_E);                                           // opadaj¹ce zbocze Enable potwierdzaj¹ce dane DB4 .. DB7
    _delay_us(100);
    //for(unsigned int i=0; i<10; i++) _delay_us(10);                           // opóŸnienie 100us
    //****dodatkowe parametry inicjalizacji****
    LCD_SEND(0b00101000, instrukcja);                                           // Konfiguracja sterownika- interfejs 4-bitowy, wyœwietlacz 2 liniowy, matryca 5x8 punktów
    LCD_SEND(0b00000110, instrukcja);                                           // Konfiguracja trybu- imkrementacja adresu
    LCD_SEND(0b00001100, instrukcja);                                           // Konfiguracja sterowania wyœwietlaczem- w³¹cz wyœwietlanie, kursow wy³¹czony, miganie kursora wy³¹czone

    LCD_Czysc();

}



void LCD_ZapiszText(char * text)
{
    while(*text)
        LCD_SEND(*text++,dane);
}

void LCD_XY(unsigned char X, unsigned char Y)                                   // ustawia kursor na pozycji X,Y, gdzie X to nr pola poziomo a Y to nr pola w pionie. 0,0 to pozycja pocz¹tkwa.
{
    LCD_SEND(0b10000000 | (X + (0x40 * Y)),instrukcja);
}


void LCD_LICZBA(unsigned int n)                                                 // Wyœwietla liczbê 3-cyfrow¹, wystêpuj¹ zera wiod¹ce,
{                                                                               // liczba zajmuje 3 pola od nastêpnej ni¿ aktualna pozycja kursowa
    if(n/100)
    {
        LCD_SEND(48+(n/100),dane);
        n%=100;
        LCD_SEND(48+(n/10),dane);
    }
    else
    {
        n%=100;
        if(n/10)
            LCD_SEND(48+(n/10),dane);
    }
    n%=10;
    LCD_SEND(48+n,dane);
}

void POLSKIE_ZNAKI(void)                                                        // Procedura wprowadzaj¹ca polskie znaki do pamiêci CGADR
{
    unsigned int znaki_polskie[64]={0,0,14,1,15,17,15,3,2,4,14,16,16,17,14,0,0,0,14,17,31,16,14,3,12,4,6,12,4,4,14,0,2,4,22,25,17,17,17,0,2,4,14,17,17,17,14,0,2,4,14,16,14,1,30,0,4,0,31,2,4,8,31,0};  // tablica 8 polskich znaków w kolejnoœci: ¹, æ, ê, ³, ñ, ó, œ, ¿
    LCD_SEND(0b01000000, instrukcja);                                           // wys³ane dane zostan¹ zapisane do CGADR wyœwietlacza
    for(unsigned int l=0;l<64;l++)
        LCD_SEND(znaki_polskie[l], dane);                                       // zapisanie pamiêci CGADR
    LCD_SEND(0b10000000, instrukcja);                                           // nastêpne dane bêd¹ wysy³ane do pamiêcie DDRAM
}

void ZNAKI_SPEC(void)                                                           // Procedura wprowadzaj¹ca polskie znaki do pamiêci CGADR
{
    unsigned int znaki_spec[8]={6,6,20,31,12,14,10,18};                         // znak osoby w ruchu
    LCD_SEND(0b01000000, instrukcja);                                           // wys³ane dane zostan¹ zapisane do CGADR wyœwietlacza
    for(unsigned int l=0;l<8;l++)
        LCD_SEND(znaki_spec[l], dane);                                          // zapisanie pamiêci CGADR
    LCD_SEND(0b10000000, instrukcja);                                           // nastêpne dane bêd¹ wysy³ane do pamiêcie DDRAM
}


//*****************************************************************************
//*****************************************************************************
//*********************** Przyk³adowe u¿ycie funkcji***************************
/*
 LCD_Ini();
 LCD_XY(3,1);
 LCD_LICZBA(98);
 LCD_ZapiszText("  Tomek Jokiel ");
 LCD_XY(0,1);
 LCD_ZapiszText(" biblioteka LCD ");
 LCD_SEND(84, dane);                                                            // literka "T" w kodzie ASCI ma nr 84
 LCD_Czysc();
 */
