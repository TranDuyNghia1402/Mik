/*
 * Counter.c
 *
 * Created: 11/15/2023 10:37:58 AM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*----- Generate Pulse -----*/
ISR(TIMER1_OVF_vect) {
	PORTB ^= (1 << PB1);
	TCNT1 = 3036;
}

int main(void)
{
	DDRB |= (1 << DDB1);					// Set PB1 as OUTPUT to generate pulse on PB1
	DDRA = 0xFF;							// Set PortA as OUTPUT
    /****** Setup Counter on Timer 0 ******/
	DDRB &= ~(1 << DDB0);					// Set PB0 (T0) as INPUT
	PORTB |= (1 << PB0);					// Pull-up resistor
	TCCR0 |= (1 << CS02) | (1 << CS01);		//	External clock source on T0 pin. Clock on falling edge
	/**************************************/
	
	/****** Setup Delay on Timer 1 ******/
	/***** f_pulse bang bao nhieu thi tu tinh nhe *****/
	TCCR1A = 0;
	TCCR1B |= (1 << CS11) | (1 << CS10);
	TCNT1 = 3036;	
	TIMSK |= (1 << TOIE1);
	/************************************/
	
	sei();
    while (1) 
    {
		PORTA = TCNT0;		// Display TCNT0 value on PortA
    }
}

