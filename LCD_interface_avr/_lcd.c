/*
 * _lcd.c
 *
 * Created: 16-09-2018 11:31:46
 *  Author: _shivaakriti
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void sys_init();
void port_init();
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void enable(void);
void set_bit(unsigned int);
void clear_bit(unsigned int);
void lcd_goto(unsigned int x,unsigned int y);
unsigned char che='a';

int main(void)
{
	sys_init();
	lcd_cmd(0x01);	//(0x01)clear screen
	lcd_cmd(0x02);	//(0x02)home cursor
	lcd_cmd(0x06);	//(0x04)|entry mode i/d=1(0x02)
	lcd_cmd(0x0f);	//(0x08)|display on(0x04)|cursor on(0x02)|blink(0x01)
	lcd_cmd(0x14);	//(0x10)|move cursor(0x00)| shift right(0x04)
	lcd_cmd(0x80);	//(0x80)|set ddram(0x00) first line for second line(0x40)
    lcd_data(che);
		/*lcd_cmd(0x14);
		lcd_cmd(0x06);
		lcd_cmd(0x0e);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_data('a');*/
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
	clear_bit(0);		//PA0 is RS(register selection bit) =0(for instruction register)
	enable();			//enable pulse
}

void lcd_cmd(unsigned char ch){
	PORTA=(ch&0xf0);		//selecting higher nibble of ch
	clear_bit(0);			//PA0(RS) for instruction set
	enable();
	ch=(ch<<4);				//selecting lower nibble
	PORTA=(ch&0xf0);
	clear_bit(0);
	enable();
}

void lcd_data(unsigned char ch){
	PORTA=(ch&0xf0);		//higher nibble
	set_bit(0);
	enable();
	ch=(ch<<4);			//lower nibble
	PORTA=(ch&0xf0);
	set_bit(0);
	enable();
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str++);
	}
}

void lcd_goto(unsigned int x,unsigned int y){
	if(x==0)
	lcd_cmd(0x80|y);
	if(x==1)
	lcd_cmd(0xc0|y);
}

void clear_bit(unsigned int bit){
	PORTA= PORTA&(~(1<<bit));
}

void set_bit(unsigned int bit){
	PORTA=(PORTA|(1<<bit));
}

void enable(void){
	set_bit(2);
	_delay_ms(20);
	clear_bit(2);
	_delay_ms(20);
	
}