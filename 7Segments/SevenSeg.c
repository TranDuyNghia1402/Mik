/*
 * SevenSegCounter.c
 *
 * Created: 11/15/2023 9:37:03 AM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SEVEN_SEGMENTS_ENABLE()				DDRC = 0xFF;
#define SEVEN_SEGMENTS_DISPLAY(number)		PORTC = number;
#define DIP_SELECT_ENABLE()					DDRA = 0x0F;

#define DIP0_SELECT()						PORTA = 0x01
#define DIP1_SELECT()						PORTA = 0x02
#define DIP2_SELECT()						PORTA = 0x04
#define DIP3_SELECT()						PORTA = 0x08

unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
volatile unsigned int count = 0;
uint8_t dozens;
uint8_t hundreds;
uint8_t thousands;
uint8_t units;

void splitNumber(int number);

ISR(TIMER1_OVF_vect) {
	count++;
	if (count > 9999)
		count = 0;
}

int main(void)
{
	/****** 7Seg Initial ******/
	SEVEN_SEGMENTS_ENABLE();
	DIP_SELECT_ENABLE();
	/**************************/
    /****** Generate Delay with timer 1******/
	TCCR1A = 0;								// Normal mode
	TCCR1B |= (1 << CS11) | (1 << CS10);	// PreScaler = 64
	TIMSK |= (1 << TOIE1);
	sei();
	/***************************************/
    while (1) 
    {
		splitNumber(count);
		DIP0_SELECT();	
		SEVEN_SEGMENTS_DISPLAY(numbers[units]);
		_delay_us(200);	
		
		DIP1_SELECT();
		SEVEN_SEGMENTS_DISPLAY(numbers[dozens]);
		_delay_us(200);
			
		DIP2_SELECT();
		SEVEN_SEGMENTS_DISPLAY(numbers[hundreds]);
		_delay_us(200);	
		
		DIP3_SELECT();
		SEVEN_SEGMENTS_DISPLAY(numbers[thousands]);
		_delay_us(200);	
    }
}

void splitNumber(int number) {
	units = number % 10;
	dozens = (number / 10) % 10;
	hundreds = (number / 100) % 10;
	thousands = number / 1000;
}


