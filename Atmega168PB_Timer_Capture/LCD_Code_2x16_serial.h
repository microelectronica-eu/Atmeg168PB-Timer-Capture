/*****************************************************

         Library for 2x16 LCD


*****************************************************/

#ifndef __LCD_Code_2x16
#define __LCD_Code_2x16

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>

#define RS_ON  PORTD |= (1<<PD6) // on
#define RS_OFF PORTD &= ~(1<<PD6) // off

#define E_ON   PORTD |= (1<<PD7) // on
#define E_OFF  PORTD &= ~(1<<PD7) // off

//# define RW_on PORTD |= (1<<PD6) // on
//# define RW_off PORTD &= ~(1<<PD6) // off

// For shifting data to LCD
# define Serial_Data_on PORTE |= (1<<PE0) // on
# define Serial_Data_off PORTE &= ~(1<<PE0) // off

# define Serial_CLK_on PORTE |= (1<<PE1) // on
# define Serial_CLK_off PORTE &= ~(1<<PE1) // off


void init_LCD(void);
void write_data(unsigned char Data_LCD);
void write_inst(unsigned char comand_LCD);
void delay(void);
void print_string(char * message);
void print_char(char c);
void Serial_send(unsigned char x);


	 
	 
#endif