/*
 * _lcd_uart_char.c
 *
 * Created: 16-09-2018 14:14:50
 *  Author: _shivaakriti
 */ 
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <util/delay.h>
#include <avr/io.h>

void sys_init();
void port_init();
void lcd_init();
void uart_init(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void clear_bit(unsigned int);
void set_bit(unsigned int);
void enable();
void lcd_goto(unsigned int ,unsigned int);
void uart_rx();

unsigned char ch;


int main(void)
{
	sys_init();
	lcd_cmd(0x01);	//clear screen
	lcd_cmd(0x0e);	//display on and cursor on and blink on
	lcd_cmd(0x14);	//move cursor left to right
	lcd_cmd(0x80);	//set ddram addr.
	lcd_cmd(0x06);	//cursor left to right
	lcd_cmd(0x02);	//home cursor
	
	
    while(1)
    {
       uart_rx();
	   
	   _delay_ms(300); 
    }
}

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

void uart_init(unsigned int ubrr){
	/*set baud rate*/
	UBRR1H=(unsigned char)(ubrr>>8);
	UBRR1L=(unsigned char)ubrr;
	/*enable trans and rec*/
	UCSR1B=(1<<RXEN1)|(1<<TXEN1);
	/*set frame format*/
	UCSR1C=(1<<UCSZ11)|(1<<UCSZ10);
}

void lcd_init(){
	lcd_cmd(0x28);		//(0x20)Function set|(0x08)4bit and 2 line
	clear_bit(0);
	enable();
}
void lcd_cmd(unsigned char ch){
	PORTA=(ch&(0xf0));		//higher nibble
	clear_bit(0);			//instruction reg.
	enable();
	ch=ch<<4;				//lower nibble
	PORTA=(ch&(0xf0));
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

void uart_rx(){
	PORTC=~(0x03);
	while(!(UCSR1A&(1<<RXC1)));
	PORTC=~(0x30);
	ch=UDR1;
	/*wrong word warning*/
	if(ch=='a'){
		set_bit(3);
		_delay_ms(100);
		clear_bit(3);
	}
	//display on lcd
	lcd_data(ch);
	
}

void lcd_data(unsigned char c){
	PORTC=~(0x06);
	PORTA=(c&0xf0);
	set_bit(0);
	enable();
	c=c<<4;
	PORTA=(c&0xf0);
	set_bit(0);
	enable();
}