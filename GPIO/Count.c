/*
 * CountTo255.c
 *
 * Created: 11/13/2023 6:00:26 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA = 0xFF;		// Set PORTA as OUTPUT;
    while (1) 
    {
		for (uint8_t i = 0; i < 256; i++) {
			PORTA = i;
			_delay_ms(500);
		}
    }
}

