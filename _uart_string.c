/*
 * _uart_string.c
 *
 * Created: 13-09-2018 04:24:59
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-2
#include <avr/io.h>
#include<util/delay.h>

void sys_init(void);
void port_init(void);
void uart_init(unsigned int);
void uart_rx(void);
void uart_tx(void);

unsigned char str[50];

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
	/* Set baud rate */
	UBRR1H=(unsigned char)(ubrr>>8);
	UBRR1L=(unsigned char)ubrr;
	
	/* Enabling receiver and transmitter */
	UCSR1B=(1<<RXEN1)|(1<<TXEN1);
	
	/* Set frame format:8bit 1stopbit */
	UCSR1C=(3<<UCSZ10);
		
}

void uart_rx(){
	int i=0;
	do 
	{
		while (!(UCSR1A&(1<<RXC1)));
		str[i]=UDR1;
	} while (str[i++]!='\r');
	str[i]='\0';
}

void uart_tx(){
	int i=0;
	while(str[i]!='\0') 
	{
		while(!(UCSR1A&(1<<UDRE1)));
		UDR1=str[i];
		i++;
	}
	
}