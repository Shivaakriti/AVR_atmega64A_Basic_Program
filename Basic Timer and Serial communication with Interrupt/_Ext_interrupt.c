/*
 * _Ext_interrupt.c
 *
 * Created: 15-09-2018 00:16:22
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>

void sys_init(void);
void port_init(void);
void extint_init(void);

int main(void)
{
	sys_init();
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void sys_init(){
	port_init();
	extint_init();
}

void extint_init(){
	EICRB=0x00;
	EIMSK=(1<<INT7)|(1<<INT6);
}

void port_init(){
	DDRC=0xff;
	DDRE=0x00;
	PORTC=~0x00;
	PORTE=0xff;
}

ISR(INT6_vect){
	cli();
	PORTC=~(0x03);
	sei();
}
ISR(INT7_vect){
	cli();
	PORTC=~(0x30);
	sei();
}