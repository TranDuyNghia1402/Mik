/*
 * Button.c
 *
 * Created: 11/13/2023 3:52:00 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB &= ~(1 << DDB0);	// Set DB0 as INPUT
	PORTB |= (1 << PINB0);	// Pull-up resistor
	
	DDRA = 0xFF;			// Set PORTA as OUTPUT
    while (1) 
    {
		if (PINB & (1 << PINB0)) {
			PORTA = 0xFF;
		} 
		else {
			PORTA = 0;
		}
	}
}

