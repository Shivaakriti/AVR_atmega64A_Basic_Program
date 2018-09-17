#include "_delay_header.h"
void sys_init(){
	port_init();			
	timer_init();
}

void port_init(){
	DDRC=0xff;				//setting data direction bit 1 for output
	PORTC=0x0f;				//initializing port c to 0x00 for making all led ON 
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