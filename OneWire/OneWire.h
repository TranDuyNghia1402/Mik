/*
 * OneWire.h
 *
 * Created: 11/16/2023 1:54:15 PM
 *  Author: Tran Duy Nghia
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#define onewire_PORT PORTB
#define onewire_DDR DDRB
#define onewire_PIN PINB

void onewire_init(unsigned char onewire_pin);
unsigned char onewire_reset(void);
void onewire_writebit(unsigned char b);
unsigned char onewire_readbit(void);
void onewire_writebyte(unsigned char byte);
unsigned char onewire_readbyte(void);

#endif /* ONEWIRE_H_ */