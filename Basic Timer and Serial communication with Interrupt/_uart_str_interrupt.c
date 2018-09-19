/*
 * _uart_char_interrupt.c
 *
 * Created: 9/16/2018 5:14:51 AM
 * Author : cReAtiVe
 */ 
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sys_init(void);
void port_init(void);
void uart_init(unsigned int);


unsigned char *str;


int main(void)
{
	sys_init();
	sei();
    /* Replace with your application code */
    while (1) 
    {
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
	cli();
	/*set baud rate*/
	UBRR1H=(unsigned char)(ubrr>>8);
	UBRR1L=(unsigned char)ubrr;
	UCSR1A=(1<<UDRE1);
	/*enabling interrupt and receiver*/
	UCSR1B=(1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	/*set frame format*/
	UCSR1C=(3<<UCSZ10);
	
}

ISR(USART1_RX_vect){
	cli();
/*	PORTC=~(0x03);
	static int i=-1;
	do 
	{										check how to take data again
		str[i]=UDR1;
		i++;
		PORTC=~(PORTC);
		sei();
	} while (str[i]!='\r');
	str[i]='\0';*/
	PORTC=~(PORTC);
	_delay_ms(500);
	UCSR1B|=(1<<UDRIE1);
	sei();	
}


ISR(USART1_UDRE_vect){
	cli();
	int i=0;
	while (str[i]!='\0')
	{
		UDR1=str[i];
		i++;
	}
	PORTC=0x0f;
	_delay_ms(500);
	UCSR1B=(1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1)|(0<<UDRIE1);
	sei();
}


