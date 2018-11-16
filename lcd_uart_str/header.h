#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sys_init();
void port_init();
void lcd_init();
void uart_init(unsigned int);

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_goto(unsigned int x,unsigned int y);

char * uart_rx(char *);
void uart_tx(void);

void clear_bit(unsigned int);
void set_bit(unsigned int);
void enable();