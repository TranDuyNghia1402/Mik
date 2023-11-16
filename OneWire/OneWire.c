/*
 * OneWire.c
 *
 * Created: 11/16/2023 1:54:47 PM
 *  Author: Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "OneWire.h"

unsigned char onewire_DQ;

void onewire_init(unsigned char onewire_pin)
{
    onewire_DQ = onewire_pin;
}

unsigned char onewire_reset(void) {
	unsigned char i;
    //Set connected pin as Output and put it low
	onewire_DDR |= (1<<onewire_DQ);
    onewire_PORT &= (~ (1<<onewire_DQ));
	//low for 480us
    _delay_us(480);

	//release line but set connected pin as Input
	onewire_DDR &= ~(1<<onewire_DQ); //input
	//wait for 70uS
    _delay_us(70);

	//get value and wait 410us
	i = (onewire_PIN & (1<<onewire_DQ)) >> onewire_DQ;
	_delay_us(410);

	//return the read value,
    //0= device on bus, 1= no device on bus
	return i;
}

/////////////////////////////////////////
//This function write a bit on the bus
void onewire_writebit(unsigned char b){
	//low for 6uS
	onewire_DDR |= (1<<onewire_DQ); //output
    onewire_PORT &= ~ (1<<onewire_DQ); //low
	_delay_us(6);

    //if we want to write 1, release the line
    //if not keep it low)
	if(b)
		onewire_DDR &= ~(1<<onewire_DQ); //input

	//wait 54uS and release the line
	_delay_us(54);
	onewire_DDR &= ~(1<<onewire_DQ); //input
    //wait for another 10us
    _delay_us(10);
}

///////////////////////////////////////////////////
//This function read a bit on the bus
unsigned char onewire_readbit(void){
	unsigned char b=0;

	//low for 5uS
	onewire_PORT &= ~ (1<<onewire_DQ); //low
	onewire_DDR |= (1<<onewire_DQ); //output
	_delay_us(5);

	//release line and wait for 15uS
	onewire_DDR &= ~(1<<onewire_DQ); //input
	_delay_us(10);

	//read the value
	if(onewire_PIN & (1<<onewire_DQ))
		b=1;

	//wait 55uS and return read value
	_delay_us(55);
	return b;
}

/*
 * write one byte
 */
void onewire_writebyte(unsigned char byte){
	unsigned char i=8;
	while(i--){
		onewire_writebit(byte&1);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
unsigned char onewire_readbyte(void){
	unsigned char i=8, data=0;
	while(i--){
		data >>= 1;
		data |= (onewire_readbit()<<7);
	}
	return data;
}