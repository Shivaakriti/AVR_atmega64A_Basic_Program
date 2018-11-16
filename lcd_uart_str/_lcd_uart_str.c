/*
 * _lcd_uart_str.c
 *
 * Created: 16-09-2018 15:41:17
 *  Author: _shivaakriti
 */ 


#include "header.h"


int main(void)
{
	sys_init();
	lcd_cmd(0x06);			//(0x04)|cursor posn inc.(0x02)=1
	lcd_cmd(0x0f);			//(0x08)|display on(0x04)|cursor on(0x02)|blink(0x01)
	lcd_cmd(0x14);			//(0x10)|cursor move right(0x04)
	lcd_cmd(0x80);		//(0x80)|(0x00)set ddram addr.
	lcd_cmd(0x01);			//clear screen
	
	lcd_cmd(0x02);
	char st[10];
	char *str;
	str=&st;
    while(1)
    {
		str=uart_rx(str);
		_delay_ms(300);
		lcd_string(str);
        //TODO:: Please write your application code 
    }
}