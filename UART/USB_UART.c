/*
 * UART_Example.c
 *
 * Created: 11/15/2023 10:53:26 AM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void UART_Init(unsigned long BAUD_RATE);			// Initial UART and set BaudRate
void UART_TransmitByte(unsigned char data);		// Transmit 1 byte
unsigned char UART_ReceiveByte();				// Receive 1 byte
void UART_Transmit(const char *data);			// Transmit multi bytes

int main(void)
{
    UART_Init(9600);
	UART_Transmit("Hello, World\r\n");
	
    while (1) 
    {
		unsigned char data = UART_ReceiveByte();
		UART_TransmitByte(data);
		_delay_ms(200);
    }
}

void UART_Init(unsigned long BAUD_RATE) {
	UBRRH = 0; UBRRL = 0; UCSRC = 0; UCSRB = 0;
	unsigned int ubrr = (F_CPU / (16 * BAUD_RATE)) - 1;	// Calculate UBRR value
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	UCSRB = (1 << TXEN) | (1 << RXEN);		// Enable Transmit and Receive 
	/*  Set frame format: 8-bit data, 1stop bit   */
	/*  Asynchronous USART, non-parity mode   */
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);	
}

void UART_TransmitByte(unsigned char data)
{
	while(!(UCSRA & (1 << UDRE)));		// wait if the transmit buffer (UDR) is ready to receive new data
	UDR = data;
}

unsigned char UART_ReceiveByte() {
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}

void UART_Transmit(const char *data)
{
	while(*data)
		UART_TransmitByte(*data++);
}