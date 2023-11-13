/*
 * BrightLed.c
 *
 * Created: 11/13/2023 5:31:03 PM
 * Author : Tran Duy Nghia
 *
 *	Use PWM to change the brightness of a led
 *	Use Timer 0 to generate PWM output on PB3 (OC0)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char brightness = 0;

ISR(TIMER1_OVF_vect) {
	TCNT1 = 34286;			// Reset TCNT1
	brightness += 25;		// Increase brightness
}

int main(void)
{
	DDRB |= (1 << PB3);						// Set PB3 as OUTPUT
    /*----- Timer 0 -----*/			
	TCCR0 |= (1 << CS00);					// PreScaler = 1
	TCCR0 |= (1 << WGM01) | (1 << WGM00);	// Fast PWM, Top = 0xFF
	TCCR0 |= (1 << COM01);					// Clear on Compare Match, non-inverting mode
	TCNT0 = 0;								// Reset TCNT0
	OCR0 = 0;								// Compare match
	/*------- PWM -------*/
	
	/*----- Timer 1 -----*/
	TCCR1B |= (1 << CS12);					// Normal mode, PreScaler = 256
	TCNT1 = 34286;							// TCNT1 = 3036
	TIMSK |= (1 << TOIE1);					// Overflow mode
	/*----- Delay 1s -----*/
	
	sei();
    while (1) 
    {
		if (brightness >= 255) 
			brightness = 0;					// Reset brightness
		OCR0 = brightness;					// Set OCR0
    }
}

