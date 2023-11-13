/*
 * LedFunctionSelect.c
 *
 * Created: 11/13/2023 4:09:04 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void leftToRight(void);
void rightToLeft(void);

unsigned char state = -1;

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;		// Set PORTA as OUTPUT
	PORTA = 0xFF;
	DDRB &= ~(1 << DDB0) | ~(1 << DDB1);	// Set PINB0 & PINB1 as INPUT
	PORTB |= (1 << PB0) | (1 << PB1);		// Pull-up resistor
    while (1) 
    {
		if (PINB & (1 << PINB0)) {
			state = 0;
			PORTA = 0x01;
		}
		if (PINB & (1 << PINB1)) {
			state = 1;
			PORTA = 0x80;
		}
		if (state) 
			leftToRight();
		else 
			rightToLeft();
    }
}

void leftToRight(void) {
	PORTA = PORTA << 1;
	_delay_ms(250);
	if (PORTA == 0) {
		PORTA = 0x01;
		_delay_ms(250);
	} 
}

void rightToLeft(void) {
	PORTA = PORTA >> 1;
	_delay_ms(250);
	if (PORTA == 0) {
		PORTA = 0x80;
		_delay_ms(250);
	}
}