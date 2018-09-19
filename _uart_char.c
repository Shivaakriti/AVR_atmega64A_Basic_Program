/*
 * _uart_char.c
 *
 * Created: 12-09-2018 03:09:30
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>

void sys_init(void);
void port_init(void);
void uart_init(unsigned int);
void uart_rx(void);
void uart_tx(void);

unsigned int data;

int main(void)
{
	sys_init();
    while(1)
    {
		uart_rx();
		_delay_ms(100);
		uart_tx();
    }
}

void sys_init(){
	port_init();
	uart_init(MYUBRR);
}

void port_init(){
	DDRC=0xff;
	PORTC=0x00;
}

void uart_init(unsigned int ubrr){
	/*set Baud rate*/
	UBRR1H=(unsigned char)(ubrr>>8);
	UBRR1L=(unsigned char)ubrr;
	
	/*ENable receiver and transmitter*/
	UCSR1B=(1<<TXEN1)|(1<<RXEN1);
	
	/*Set frame format:8bit,2stop bit*/
	UCSR1C=(3<<UCSZ10);
}

void uart_rx(){
	while(!(UCSR1A&(1<<RXC1)));
	data=UDR1;
}

void uart_tx(){
	while(!(UCSR1A&(1<<UDRE1)));
	UDR1=data;
}