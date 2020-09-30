
#include <avr/io.h>
#include "LCD_Code_2x16_serial.h"


void print_string(char * message){   
	
	// Write message to LCD (C string type)
     while (*message)
	 {            // Look for end of string
        print_char(*message++);
     }

} 	
	
void print_char(char c){   // print one character , can be used to send one character 
    
	    unsigned char send_data;
	    send_data=c;
        write_data(send_data) ;
}
		
		
 void init_LCD(void)
 {  
	//RW_off;
    write_inst(0x01)  ; // clr LCD
    write_inst(0x38)  ; //comad_LCD=0x38 ; /*//Function set, ;Data 8 bit_2 line font 5x7  00111000 */
    write_inst(0x0C)  ; //comad_LCD=0x0C ; /*///Display on,  00001100   E = cursor on */
    write_inst(0x06)  ; //comad_LCD=0x06 ; /*//Entry mode, Set increment 00000110 */
 }
 
 void write_inst(unsigned char comand_LCD)
  {
    RS_OFF ;
    Serial_send(comand_LCD) ;
    E_ON ;
    delay();
    E_OFF ;
  }
 
 void write_data(unsigned char Data_LCD)
 { 
  RS_ON;
  Serial_send(Data_LCD);
  E_ON;
  delay();
  E_OFF  ;
 }

void Serial_send(unsigned char x){
	unsigned char i;
	for(i=8;i>0;i--){
		Serial_CLK_off ;
		if((x&0x80)){
			Serial_Data_on;
			} else {
			Serial_Data_off;
		}
		Serial_CLK_on;
		x <<= 1;
	}
}
void delay(void)
 {
 	unsigned int i;
 	
 	for(i=0;i<10000;i++)
 	{
	 	asm("nop");
	 	
 	}
  }

