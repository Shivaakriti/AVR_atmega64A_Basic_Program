/*
 * _timer1_ctcmode.c
 *
 * Created: 11-09-2018 02:42:57
 *  Author: _shivaakriti
 */ 


#include <avr/io.h>

void sys_init(void);
void port_init(void);
void timer_init(void);
void delay(unsigned int);

int main(void)
{
	sys_init();
    while(1)
    {
		PORTC=~(0X03);
		delay(1000); 
		PORTC=~(0x0f);
		delay(1000);
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
	TCCR1B=0x09;
	TCCR1C=0x00;
	TCNT1=0x00;
	OCR1A=0xC180;
}

void delay(unsigned int x){
	int i;
	for(i=0;i<x;i++){
		while(!(TIFR&(1<<OCF1A)));
		TIFR=(1<<OCF1A);
	}
}