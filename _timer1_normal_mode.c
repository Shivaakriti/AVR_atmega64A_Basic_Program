/*
 * _timer1_normal_mode.c
 *
 * Created: 10-09-2018 12:54:15
 *  Author: _shivaakriti
 */ 


#include <avr/io.h>

void sys_init(void);				//declaration of system initialization for micro controller
void port_init(void);				//declaration of port register initialization
void timer_init(void);
void delay(unsigned int);				//declaration of timer register initialization


int main(void)
{
	sys_init();
	
    while(1)
    {
		delay(1000);
		PORTC=~(0x0f);
		delay(1000);
		PORTC=~(0X33);
		
    }
	return 0;
}

void sys_init(){
	port_init();			
	timer_init();
}

void port_init(){
	DDRC=0xff;				//setting data direction bit 1 for output
	PORTC=0x00;				//initializing port c to 0x00 for making all led ON 
}

void timer_init(){
	TCCR1A=0X00;
	TCCR1B=0X01;
	TCCR1C=0X00;
	TCNT1=0xC180;			//0xC180 use for providing 1ms delay for 16Mhz
}

void delay(unsigned int x){
	int i;
	
	for(i=0;i<x;i++){
		while(!(TIFR&(1<<TOV1)));
		TIFR=(1<<TOV1);
	}
}