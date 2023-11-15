/*
 * ADC_Example.c
 *
 * Created: 11/15/2023 4:58:44 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

void ADC_Init(void);
unsigned int ADC_Read_Data(unsigned char ADC_pin);

unsigned int data;

int main(void)
{
	UART_Init(19200);
	UART_Transmit("Hello, World\r\n");
	ADC_Init();
    while (1) 
    {
		data = ADC_Read_Data(A6);
		UART_PrintInteger(data);
		UART_Transmit("\r\n");
    }
}

void ADC_Init(void) {
	ADMUX |= (1 << REFS0);	// AVCC with external capacitor at AREF pin
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

unsigned int ADC_Read_Data(unsigned char ADC_pin) {
	unsigned int data;
	ADMUX |= ADC_pin;
	_delay_ms(10);
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1 << ADIF)));
	data = ADCW;
	ADCSRA |= (1 << ADIF);
	return data;
}


