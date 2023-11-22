/*
 * LCD_1602.c
 *
 * Created: 11/16/2023 11:58:25 AM
 *  Author: Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "LCD_1602.h"

void LCD_Init(void) {
	RS_DIR |= (1 << RS_PIN);				// A2 output - RS
	RS_PORT &= ~(1 << RS_PIN);				// A2 LOW
	EN_DIR |= (1 << EN_PIN);				// D6 output - EN
	EN_PORT &= ~(1 << EN_PIN);				// D6 LOW
	DATA_DIR |= DATA_PIN;					// Set Data as Output
	LCD_Command(0xFF);
	_delay_ms(1);  
	LCD_Command(0x83);
	_delay_ms(1);    
	LCD_Command(0x82);
	_delay_ms(1); 
	LCD_Command(0x28);						// Function Set: 4-bit, 2 Line, 5x8 Dots
	_delay_ms(10);
	LCD_Command(0x01);
	_delay_ms(200);
	LCD_Command(0x0C);						// Display on Cursor off
	_delay_ms(10);
	LCD_Command(0x06);						// Entry Mode
	_delay_ms(10);
}	
							
void LCD_Command(unsigned char cmd) {
	// send MSB
	DATA_PORT = (cmd);
	RS_PORT &= ~((1 << RS_PIN));					// PA2 RS low
	_delay_ms(1);
	EN_PORT |= (1 << EN_PIN);						// PD6 EN high
	EN_PORT &= ~(1 << EN_PIN);						// PD6 EN low
	_delay_ms(1);	
	// send LSB
	DATA_PORT = (cmd << 4);
	_delay_ms(1);
	EN_PORT |= (1 << EN_PIN);						// PD6 EN high
	EN_PORT &= ~(1 << EN_PIN);						// PD6 EN low
	_delay_ms(1);
}	
								
void LCD_Data(unsigned char data) {
	// send MSB
	DATA_PORT = (data);
	RS_PORT |= (1 << RS_PIN);						// PA2 RS high
	_delay_ms(1);
	EN_PORT |= (1 << EN_PIN);						// PD6 EN high
	EN_PORT &= ~(1 << EN_PIN);						// PD6 EN low
	_delay_ms(1);
	
	// send LSB
	DATA_PORT = (data << 4);
	_delay_ms(1);
	EN_PORT |= (1 << EN_PIN);						// PD6 EN high
	EN_PORT &= ~(1 << EN_PIN);						// PD6 EN low
	_delay_ms(1);
}	
									
void LCD_SetCursor(int x, int y) {
	switch (x) {
		case 0:
		y |= 0x80;
		break;
		case 1:
		y |= 0xC0;
		break;
	}
	LCD_Command(y);
}	
		
void LCD_Write(const char *data) {
	while (*data) {
		LCD_Data(*data++);
	}
}

void LCD_Clear(void) {
	LCD_Command(0x01);
	_delay_ms(200);
}
