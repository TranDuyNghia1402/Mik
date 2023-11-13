/*
 * Delay.c
 *
 * Created: 11/13/2023 5:25:56 PM
 * Author : Tran Duy Nghia
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// Interrupt Service Routine
ISR(TIMER1_OVF_vect) {
	PORTA = ~PORTA;
}

int main(void)
{
	DDRA = 0xFF;
    /*----- Timer 1 -----*/
    // Generate delay 0.5s
    TCCR1B |= (1 << CS10) | (1 << CS11);	// Normal mode, Prescaler = 64
    TCNT1 = 3036;							// TCNT1 = 3036
    TIMSK |= (1 << TOIE1);					// Overflow mode
    /*------------------*/
	
	sei();		// Enable Global Interrupt
    while (1) 
    {
    }
}

