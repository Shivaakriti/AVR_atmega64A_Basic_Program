/*
 * _lcd_string_withGOTO.c
 *
 * Created: 16-09-2018 13:28:01
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void sys_init();
void port_init();
void lcd_init();
void lcd_cmd(unsigned char);
void clear_bit(unsigned int);
void enable();
void set_bit(unsigned int);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_goto(unsigned int x,unsigned int y);

char st[]="AC 30 ";
char st1[]="SL 121";

int main(void)
{
	sys_init();
	lcd_cmd(0x06);			//(0x04)|cursor posn inc.(0x02)=1
	lcd_cmd(0x0f);			//(0x08)|display on(0x04)|cursor on(0x02)|blink(0x01)
	lcd_cmd(0x14);			//(0x10)|cursor move right(0x04)
	lcd_cmd(0x80);		//(0x80)|(0x00)set ddram addr.
	lcd_cmd(0x01);			//clear screen
		
    lcd_cmd(0x02);			//home cursor
	lcd_string(st);
	lcd_goto(1,0);
	lcd_string(st1);
	while(1)
    {
        //TODO:: Please write your application code 
    }
}

void sys_init(){
	port_init();
	lcd_init();
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