/*
 * Atmega168PB_Serial_LCD_2x16.c
 *                                                  Atentie LCD pinout modificat PD5 nu mai este folosit ca si RS .
													RS spin a devenit PD6
													R/W pin de la LCD a fost legat la masa 
													
													Attention to LCD pinout because is a small modification here . PD5 is not used as RS . RS pin has become PD6 .
													R/W pin from LCD is connected to GND . 
													this setup is uded formy development borard . 
													
													
													
 * Created: 5/15/2020 2:58:15 PM
 * Author : roburlan
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "LCD_Code_2x16_serial.h"
#include <avr/interrupt.h>

//unsigned char tabel[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

unsigned char  a1	   ;
unsigned char  b1    ;
unsigned char  c1    ;
unsigned char  d1    ;
unsigned char  e1  ;
int CountHigh = 0;
unsigned int Count = 0;

void CounterInit(void);
void math(unsigned char LCD_Address, unsigned int MATH_DATA);



ISR(TIMER1_CAPT_vect)
{
	
	Count=0;
	Count=TCNT1 ; //ICR1
 	TCNT1=0;

}


int main(void)
{
     DDRE= 0xFF ;
     DDRB= 0xFE ;
     DDRC= 0xFF;
     DDRD= 0xFF ;
     
     PORTE=0x00;
     PORTB=0x00;
     PORTC=0x00;
     PORTD=0x00;
	 init_LCD();
	 CounterInit();
	 write_inst(0x80);  // 0x80 first row 0xc0 second row
	 print_string("Timmer test");
	 sei();
	 unsigned int local ;
	 double	data1;
    while (1) 
    {
		 
		  math(0xc0,Count);
		  
		  data1=Count;
		  local=(1/((62.5*data1)/1000000000)); // Hz value
		  
		  math(0xcA,local);
		  write_data('H') ;
		  write_data('z') ;
	}
   
}

void CounterInit(void)
{   
	TCCR1B = (1<<ICNC1)|(1<<CS10); // External clock source on T1 pin. Clock on rising edge.(1<<ICNC1)|
	TIFR1  = 1<<ICF1;
	TIMSK1 = 1<<ICIE1;
	
}

void math(unsigned char LCD_Address, unsigned int MATH_DATA)
{
	unsigned int mat	  ;
    unsigned int zecemii ;
	unsigned char mii	   ;
	unsigned char sute ;
	unsigned char zeci ;
	unsigned char unitati;


   
	
	mat= MATH_DATA ;
	
	
	zecemii=mat/10000 ;
	mat=mat%10000 ;
	mii= mat/1000;
	mat= mat%1000 ;
	sute= mat/100 ;
	mat= mat%100 ;
	zeci=	mat/10  ;
	unitati= mat%10  ;

	
	a1 = zecemii + 0x30 ;
	b1 = mii + 0x30 ;
	c1 = sute + 0x30 ;
	d1 = zeci + 0x30;
	e1 = unitati + 0x30;
	
	 write_inst(LCD_Address);
	 write_data(a1) ;
	 write_data(b1) ;
	 write_data(c1) ;
	 write_data(d1) ;
	 write_data(e1) ;// 0xc5
}

