/*
 * _timer1_ctcMode_interrupt.c
 *
 * Created: 9/14/2018 4:20:46 AM
 * Author : _shivaakriti
 */ 
#define F_CPU 16000000
#define COUNT 1*(F_CPU/1024)
#include <avr/io.h>
#include <avr/interrupt.h>

void sys_init(void);
void port_init(void);
void timer_init(void);



int main(void)
{
	sys_init();
    sei();
	while (1) 
    {
    }
}

void sys_init(){
	port_init();
	timer_init();
}

void port_init(){
	DDRC=0xff;
	PORTC=0x0f;
}

void timer_init(){
	TCCR1A=0x00;
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);
	TCCR1C=0x00;
	TCNT1=0x00;
	OCR1A=COUNT;
	TIMSK=(1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect){
	cli();
	PORTC=~(PORTC);
	TCNT1=0x00;
	sei();
	
}
