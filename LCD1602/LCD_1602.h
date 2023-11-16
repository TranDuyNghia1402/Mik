/*
 * LCD_1602.h
 *
 * Created: 11/16/2023 11:49:25 AM
 *  Author: Tran Duy Nghia
 */

#ifndef LCD_1602_H_
#define LCD_1602_H_

#define RS_PIN PA2
#define RS_PORT PORTA
#define RS_DIR DDRA

#define EN_PIN PD6
#define EN_PORT PORTD
#define EN_DIR DDRD

#define DATA_PIN ((1 << PC4) | (1 << PC5) | (1 << PC6) | (1 << PC7))
#define DATA_PORT PORTC
#define DATA_DIR DDRC

void LCD_Init(void);                 // LCD Initial
void LCD_Command(unsigned char cmd); // LCD send command
void LCD_Data(unsigned char data);   // LCD send data
void LCD_SetCursor(int x, int y);    // LCD set cursor
void LCD_Write(const char *data_l);  // Print to LCD
void LCD_Clear(void);                // Clear LCD

#endif /* LCD_1602_H_ */