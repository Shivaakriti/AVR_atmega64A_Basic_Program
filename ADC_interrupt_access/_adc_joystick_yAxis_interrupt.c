/*
 * _adc_joystick_yAxis_interrupt.c
 *
 * Created: 16-09-2018 07:44:01
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void sys_init();
void port_init();
void adc_init();

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
	adc_init();
}

void port_init(){
	DDRC=0xff;
	PORTC=0x00;
}

void adc_init(){
	ADMUX=(1<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(1<<MUX1);
	ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0);
}

ISR(ADC_vect){
	cli();
	PORTC=ADCH;
	_delay_ms(100);
	sei();
}