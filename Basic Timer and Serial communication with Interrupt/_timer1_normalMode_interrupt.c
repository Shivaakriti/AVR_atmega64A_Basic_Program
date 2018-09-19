/*
 * _timer1_normalMode_interrupt.c
 *
 * Created: 14-09-2018 05:07:39
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#define PRESCALE F_CPU/1024
//#define COUNT (0xFFFF-PRESCALE)-1
#define COUNT 0x32F6
#include <avr/io.h>
#include <avr/interrupt.h>

void sys_init(void);
void port_init(void);
void timer_init(void);

int main(void)
{
	sys_init();
	sei();
    while(1)
    { 
    }
}

void sys_init(){
	port_init();
	timer_init();
}

void port_init(){
	DDRC=0xff;
	PORTC=0x00;
}

void timer_init(){
	TCCR1A=0x00;
	TCCR1B=(1<<CS10)|(1<<CS12);
	TCCR1C=0x00;
	TCNT1=COUNT;
	TIMSK=(1<<TOIE1);
}

ISR(TIMER1_OVF_vect){
	cli();
	PORTC=~PORTC;
	TCNT1=COUNT;
	sei();
}