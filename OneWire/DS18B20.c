/*
 * OneWireExampleWithDS18B20.c
 *
 * Created: 11/16/2023 1:54:02 PM
 * Author : Tran Duy Nghia
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "OneWire.h"

//commands
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define onewire_CMD_SEARCHROM 0xf0
#define onewire_CMD_READROM 0x33
#define onewire_CMD_MATCHROM 0x55
#define onewire_CMD_SKIPROM 0xcc
#define onewire_CMD_ALARMSEARCH 0xec

//stop any interrupt on read
#define onewire_STOPINTERRUPTONREAD 1

float ds18b20_getTemp();
float temp;

int main(void)
{
	onewire_init(4);
    while (1) 
    {
		temp = ds18b20_getTemp();
    }
}

float ds18b20_getTemp() {
	int temperature_l;
	int temperature_h;
	float retd = 0;

	#if onewire_STOPINTERRUPTONREAD == 1
	cli();
	#endif

	onewire_reset(); //reset
	onewire_writebyte(onewire_CMD_SKIPROM); //skip ROM
	onewire_writebyte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

	while(!onewire_readbit()); //wait until conversion is complete

	onewire_reset(); //reset
	onewire_writebyte(onewire_CMD_SKIPROM); //skip ROM
	onewire_writebyte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	//read 2 byte from scratchpad
	temperature_l = onewire_readbyte();
	temperature_h = onewire_readbyte();

	#if onewire_STOPINTERRUPTONREAD == 1
	sei();
	#endif

	//convert the 12 bit value obtained
	retd = ((temperature_h << 8) + temperature_l) * 0.0625;

	return retd;
}