/*
 * _led_blink.c
 * Created: 09-09-2018 05:34:35
 *  Author:_shivaakriti
 */ 
/*
 * PORTC is connected to led port

 */
#define F_CPU 16000000					//setting frequency of CPU cycle to 16MHz	

#define SW1 PIND6						//using switch1(port d 6th bit)
#define SW2	PIND7						//		switch2(port d 7th bit)

#include <avr/io.h>						//header file for input and output of data from avr micro controller
#include <util/delay.h>					//header file included for providing delay

void sys_init(void);					//function use for intializing the register which are used
void port_init(void);					//PORT intialiation

int main(void)
{	
	sys_init();
	while(1)												//super loop for continues working of micro controller
    {
			if((~(PIND) &(1<<SW2|1<<SW1)))					//use PIND for reading purpose;	
			{												//here comparing with 0xC0(i.e bit6,7 of port d) 
				
				PORTC=~(0x33);								//setting PORTC bit to ON led(negation is use as PORT pin are active low)
				_delay_ms(1000);
			}else{
				PORTC=~(0x0f);	
			}
	}
}

void sys_init(){
	port_init();
}
void port_init(){
	DDRC=0xFF;							//setting data direction register bit to all 1(i.e 0xFF for 8bits) as for OUTPUT DDRx=1(DDRC for PORTC)
	DDRD=0x00;							//setting data direction register bit to all 0(i.e 0x00 for 8bits) as for INPUT DDRx=0(DDRC for PORTD)
	PORTC=0X00;
	PORTD=0XFF;
}