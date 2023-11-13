/*
 * Blinky.c
 *
 * Created: 11/13/2023 3:46:43 PM
 * Author : Tran Duy Nghia
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;		// Set PORTA as OUTPUT
	PORTA = 0xFF;		// Set PORTA to HIGH
    while (1) 
    {
		PORTA = ~PORTA;		// Toggle Led on PORTA
		_delay_ms(500);		// Delay 500ms
    }
}

