/*
 * LCD_Example.c.c
 *
 * Created: 11/16/2023 11:48:29 AM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include "LCD_1602.h"

int main(void)
{
    LCD_Init();
	LCD_SetCursor(0, 0);
	LCD_Write("Hello, World!");
    while (1) 
    {
		LCD_SetCursor(1, 0);
		LCD_Write("K65 EEI");
    }
}

