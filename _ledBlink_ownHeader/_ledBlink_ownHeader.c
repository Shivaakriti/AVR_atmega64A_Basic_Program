/*
 * _ledBlink_ownHeader.c
 *
 * Created: 10-09-2018 00:19:41
 *  Author: _shivaakrirti
 */ 


#include "_delay_header.h"

int main(void)
{
	sys_init();
    while(1)
    {
       PORTC=~(0x03);								//setting PORTC bit to ON led(negation is use as PORT pin are active low)
       delay(1000);
	   PORTC=~(0x30);								//setting PORTC bit to ON led(negation is use as PORT pin are active low)
	   delay(1000);
    }
	return 0;
}
