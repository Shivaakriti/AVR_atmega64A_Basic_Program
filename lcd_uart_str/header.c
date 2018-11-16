#include "header.h"

void sys_init(){
	port_init();
	lcd_init();
	uart_init(MYUBRR);
}

void port_init(){
	DDRA=0xff;
	DDRC=0xff;
	PORTC=0x00;
}

void lcd_init(){
	lcd_cmd(0x28);
	clear_bit(0);
	enable();
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

void lcd_cmd(unsigned char ch){
	PORTA=(ch&0xf0);
	clear_bit(0);
	enable();
	ch=ch<<4;
	PORTA=(ch&0xf0);
	clear_bit(0);
	enable();
}

void clear_bit(unsigned int bit){
	PORTA=(PORTA&(~(1<<bit)));
}

void set_bit(unsigned int bit){
	PORTA=(PORTA|(1<<bit));
}

void enable(){
	set_bit(2);
	_delay_ms(20);
	clear_bit(2);
	_delay_ms(20);
}

void lcd_data(unsigned char ch){
	PORTA=(ch&0xf0);
	set_bit(0);
	enable();
	ch=ch<<4;
	PORTA=(ch&0xf0);
	set_bit(0);
	enable();
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str);
		str++;
	}
}

void lcd_goto(unsigned int x,unsigned int y){
	if(x==0)
	lcd_cmd(0x80|y);
	if(x==1)
	lcd_cmd(0xc0|y);
}

char * uart_rx(char *str){
	int i=0;
	do 
	{
		while (!(UCSR1A&(1<<RXC1)));
		str[i]=UDR1;
	} while (str[i++]!='\r');
	str[i]='\0';
	return str;
}