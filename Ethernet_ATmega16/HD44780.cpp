//  HD44780 LCD 4-bit IO mode Driver
//  (C) 2009 - 2012 Radu Motisan , radu.motisan@gmail.com , www.pocketmagic.net
//  All rights reserved.
//
//	To be used with AVR Studio 5 (avr-g++.exe)
//
//  HD44780.cpp: Definitions for LCD command instructions
//  The constants define the various LCD controller instructions which can be passed to the 
//  function lcd_command(), see HD44780 data sheet for a complete description.

#include <avr/io.h> 
#include "HD44780.h"
#include "aux_globals.h"

// PURPOSE: flush channel E
void HD44780::lcd_toggle_e(void)
{
    lcd_e_high();
    fcpu_delay_us(10);
    lcd_e_low();
}

// PURPOSE: send a character or an instruction to the LCD
void HD44780::lcd_write(uint8_t data,uint8_t rs) 
{
    // we cannot check LCD status (no read available) , so we will assume a default delay to wait for lcd to be ready
    fcpu_delay_us(500);
    //check write type
    if (rs)   
        lcd_rs_high(); //write data
    else     
        lcd_rs_low();  //write instruciton

    // configure data pins as output 
    LCD_DDR(LCD_4BIT_D4_PORT) |= _BV(LCD_4BIT_D4_PIN);
    LCD_DDR(LCD_4BIT_D5_PORT) |= _BV(LCD_4BIT_D5_PIN);
    LCD_DDR(LCD_4BIT_D6_PORT) |= _BV(LCD_4BIT_D6_PIN);
    LCD_DDR(LCD_4BIT_D7_PORT) |= _BV(LCD_4BIT_D7_PIN);

    // output high nibble first 
    LCD_4BIT_D7_PORT &= ~_BV(LCD_4BIT_D7_PIN);
    LCD_4BIT_D6_PORT &= ~_BV(LCD_4BIT_D6_PIN);
    LCD_4BIT_D5_PORT &= ~_BV(LCD_4BIT_D5_PIN);
    LCD_4BIT_D4_PORT &= ~_BV(LCD_4BIT_D4_PIN);
    if(data & 0x80) LCD_4BIT_D7_PORT |= _BV(LCD_4BIT_D7_PIN);
    if(data & 0x40) LCD_4BIT_D6_PORT |= _BV(LCD_4BIT_D6_PIN);
    if(data & 0x20) LCD_4BIT_D5_PORT |= _BV(LCD_4BIT_D5_PIN);
    if(data & 0x10) LCD_4BIT_D4_PORT |= _BV(LCD_4BIT_D4_PIN);
    lcd_toggle_e();

    // output low nibble 
    LCD_4BIT_D7_PORT &= ~_BV(LCD_4BIT_D7_PIN);
    LCD_4BIT_D6_PORT &= ~_BV(LCD_4BIT_D6_PIN);
    LCD_4BIT_D5_PORT &= ~_BV(LCD_4BIT_D5_PIN);
    LCD_4BIT_D4_PORT &= ~_BV(LCD_4BIT_D4_PIN);
    if(data & 0x08) LCD_4BIT_D7_PORT |= _BV(LCD_4BIT_D7_PIN);
    if(data & 0x04) LCD_4BIT_D6_PORT |= _BV(LCD_4BIT_D6_PIN);
    if(data & 0x02) LCD_4BIT_D5_PORT |= _BV(LCD_4BIT_D5_PIN);
    if(data & 0x01) LCD_4BIT_D4_PORT |= _BV(LCD_4BIT_D4_PIN);
    lcd_toggle_e();        

    // all data pins high (inactive) 
    LCD_4BIT_D4_PORT |= _BV(LCD_4BIT_D4_PIN);
    LCD_4BIT_D5_PORT |= _BV(LCD_4BIT_D5_PIN);
    LCD_4BIT_D6_PORT |= _BV(LCD_4BIT_D6_PIN);
    LCD_4BIT_D7_PORT |= _BV(LCD_4BIT_D7_PIN);
}


// PURPOSE:  send an instruction to the LCD
void HD44780::lcd_instr(uint8_t instr)
{
    lcd_write(instr,0);
}

// PURPOSE:  Initialize LCD to 4 bit I/O mode
void HD44780::lcd_init()
{
    // configure all port bits as output (LCD data and control lines on different ports 
    LCD_DDR(LCD_RS_PORT)    |= _BV(LCD_RS_PIN);
    LCD_DDR(LCD_E_PORT)     |= _BV(LCD_E_PIN);
    LCD_DDR(LCD_4BIT_D4_PORT) |= _BV(LCD_4BIT_D4_PIN);
    LCD_DDR(LCD_4BIT_D5_PORT) |= _BV(LCD_4BIT_D5_PIN);
    LCD_DDR(LCD_4BIT_D6_PORT) |= _BV(LCD_4BIT_D6_PIN);
    LCD_DDR(LCD_4BIT_D7_PORT) |= _BV(LCD_4BIT_D7_PIN);
    // wait 25ms or more after power-on
    fcpu_delay_us(25000);

    // initial write to lcd is 8bit 
    LCD_4BIT_D5_PORT |= _BV(LCD_4BIT_D5_PIN);  // _BV(LCD_FUNCTION)>>4;
    LCD_4BIT_D4_PORT |= _BV(LCD_4BIT_D4_PIN);  // _BV(LCD_FUNCTION_8BIT)>>4;
    lcd_toggle_e();
    fcpu_delay_us(2000); //2000        // delay, busy flag can't be checked here 

    // repeat last command
    lcd_toggle_e();      
    fcpu_delay_us(64); //64          // delay, busy flag can't be checked here 

    // now configure for 4bit mode
    LCD_4BIT_D4_PORT &= ~_BV(LCD_4BIT_D4_PIN);   // LCD_FUNCTION_4BIT_1LINE>>4
    lcd_toggle_e();
    fcpu_delay_us(2000);           // some displays need this additional delay 



    // set 4 bit IO
    lcd_instr(LCD_FUNCTION_4BIT_2LINES); // 4-bit interface, dual line,   5x7 dots 
    lcd_toggle_e();
    fcpu_delay_us(2000);           // some displays need this additional delay

    lcd_instr(LCD_ENTRY_INC_);//cursor move right, no shift display
    lcd_toggle_e();
    fcpu_delay_us(2500);           // some displays need this additional delay


    lcd_instr(LCD_DISP_ON);// display on, cursor off, blink char off
    lcd_toggle_e();
    fcpu_delay_us(2500);           // some displays need this additional delay



    lcd_home();//set cursor to home and clear the cursor

}

// PURPOSE:  send a character to the LCD
void HD44780::lcd_char(uint8_t data)
{
    if (data=='\n')
    {
        if (g_nCurrentLine >= LCD_LINES - 1)
            lcd_setline(0);
        else
            lcd_setline(g_nCurrentLine+1);
    }
    else
        lcd_write(data,1);
}




// PURPOSE:  send a null terminated string to the LCD eg. char x[10]="hello!";
void HD44780::lcd_string(char *text)
{
    char c;
    while ( (c = *text++) )  lcd_char(c);
}

void HD44780::lcd_string_format(char *szFormat, ...)
{	
    char szBuffer[256]; //in this buffer we form the message
    int NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    int LASTCHAR = NUMCHARS - 1;
    va_list pArgs;
    va_start(pArgs, szFormat);
    vsnprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    lcd_string(szBuffer);
}
// PURPOSE:  Set cursor to specified position
//           Input:    x  horizontal position  (0: left most position)
//                     y  vertical position    (0: first line)
void HD44780::lcd_gotoxy(uint8_t x, uint8_t y)
{
#if LCD_LINES==1
    lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);
#elif LCD_LINES==2
    switch (y)
    {
    case 0:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);break;
    case 1:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE2+x);break;
    default: break;
    }
#elif LCD_LINES==4
    switch (y)
    {
    case 0:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);break;
    case 1:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE2+x);break;
    case 2:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE3+x);break;
    case 3:lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE4+x);break;
    default: break;
    }
#endif
}

// PURPOSE:  Move cursor on specified line
void HD44780::lcd_setline(uint8_t line)
{
    uint8_t addressCounter = 0;
    switch(line)
    {
    case 0: addressCounter = LCD_START_LINE1; break;
    case 1: addressCounter = LCD_START_LINE2; break;
    case 2: addressCounter = LCD_START_LINE3; break;
    case 3: addressCounter = LCD_START_LINE4; break;
    default:addressCounter = LCD_START_LINE1; break;
    }
    g_nCurrentLine = line;

    lcd_instr((1<<LCD_DDRAM)+addressCounter);
}

// PURPOSE:  Clear display and set cursor to home position
void HD44780::lcd_clrscr(void)
{
    g_nCurrentLine = 0;
    lcd_instr(1<<LCD_CLR);
    fcpu_delay_us(500);
}

// PURPOSE:  Set cursor to home position
void HD44780::lcd_home(void)
{
    //g_nCurrentLine = 0;
    lcd_instr(1<<LCD_HOME);
    lcd_setline(0);
}
