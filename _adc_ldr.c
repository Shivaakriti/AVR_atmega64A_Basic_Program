/*
 * _adc_ldr.c
 *
 * Created: 15-09-2018 06:49:52
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void sys_init(void);
void port_init(void);
void adc_init(void);

int main(void)
{
	sys_init();
    while(1)
    {
		ADCSRA|=(1<<ADSC);
        while (!(ADCSRA&(1<<ADIF)));
		PORTC=ADCH;    
		_delay_ms(500);  
     }
}

void sys_init(){
	port_init();
	adc_init();
}

void port_init(){
	DDRC=0xff;
	PORTC=0x00;
}

void adc_init(){
	ADMUX=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR);
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}