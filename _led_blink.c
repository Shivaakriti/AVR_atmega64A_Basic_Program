/*
 * _led_blink.c
 * Created: 09-09-2018 05:34:35
 *  Author:_shivaakriti
 */ 
/*
 * PORTC is connected to led port

 */
#define F_CPU 16000000			//setting frequency of CPU cycle to 16MHz
#include <avr/io.h>				//header file for input and output of data from avr micro controller
#include <util/delay.h>			//header file included for providing delay

void sys_init(void);					//function use for intializing the register which are used
void port_init(void);					//PORT intialiation

int main(void)
{	sys_init();
   
	while(1)					//super loop for continues working of micro controller
    {
        PORTC=~(0x33);			//setting PORTC bit to ON led(negation is use as PORT pin are active low) 
		_delay_ms(1000);		//providing delay(in ms) which is provided by util library
		PORTC=~(0X0F);
    }
}

void sys_init(){
	port_init();
}
void port_init(){
	DDRC=0xFF;							//setting data direction register bit to all 1(i.e 0xFF for 8bits) as for OUTPUT DDRx=1(DDRC for PORTC)
	PORTC=0X00;
}