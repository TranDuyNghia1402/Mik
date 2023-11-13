/*
 * LedFunctionSelectWithInterrupt.c
 *
 * Created: 11/13/2023 4:47:52 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char state = -1;

int main(void)
{
    DDRA = 0xFF;			// Set PORTA as OUTPUT
	DDRD &= ~(1 << DDD2) | ~(1 << DDD3);	// Set PD2 & PD3 as INPUT
	PORTD |= (1 << PD2) | (1 << PD3);		// Pull-up resistor
	
    MCUCR |= (1 << ISC11);	//  The falling edge of INT1 generates an interrupt request
	MCUCR |= (1 << ISC01);	//	The falling edge of INT0 generates an interrupt request
	GICR |= (1 << INT1);	//	External Interrupt Request 1 Enable
	GICR |= (1 << INT0);	//	External Interrupt Request 0 Enable
	
	/*----- Timer 1 -----*/
	// Generate delay 0.5s
	TCCR1B |= (1 << CS10) | (1 << CS11);	
	TCNT1 = 3036;
	TIMSK |= (1 << TOIE1);
	/*------------------*/
	
	sei();					// Enable global interrupt
	while (1) 
    {
		if (PORTA == 0) {
			if (state)
				PORTA = 0x80;
			else
				PORTA = 0x01;
		}
    }
}

ISR(INT0_vect) {
	state = 0;
	PORTA = 0x01;
}

ISR(INT1_vect) {
	state = 1;
	PORTA = 0x80;
}

ISR(TIMER1_OVF_vect) {
	if (state) {
		PORTA = PORTA >> 1;
	}
	else {
		PORTA = PORTA << 1;
	}
}