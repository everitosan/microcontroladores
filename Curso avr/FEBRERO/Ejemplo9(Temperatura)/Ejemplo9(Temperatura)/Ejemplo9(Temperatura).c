/*
 * Ejemplo9_Temperatura_.c
 *
 * Created: 06/03/2013 01:37:52 p. m.
 *  Author: Everardo
 */ 


#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

void adcinit();
int readadc(char canal);
char cad[4];
int num;

int main(void)
{	/*
	vin=10mV
	vref=5v
	
	(vin*1024)/v=(.010*1024)/5=2.048
	*/
	DDRB=0x06;
	adcinit();
	lcd_init();
	
	lcd_gotoxy(3,0);
	lcd_puts("Temperatura:");
	
    while(1)
    {
		
		
		num=readadc(5)/2.048;
        itoa(num,cad, 10 );
		
		lcd_gotoxy(5,1);
		lcd_puts("    ");
		lcd_gotoxy(5,1);		
		lcd_puts(cad);		
		if(num<19)
			 PORTB=0x02;
			else if(num>22)
				PORTB=0x04;
				else
					PORTB=0x00;	
		delay_ms(400);
    }
}

void adcinit()
{
	ADMUX=0X40;
	ADCSRA=0X80;
	
}

int readadc(char canal)
{
	ADMUX=(ADMUX&0XF0)|canal; //selecion canal
	ADCSRA= ADCSRA|(1<<ADSC); //inicia conv
	
	while((ADCSRA&(1<<4))==0); //espera a que se completa la conversion
	return ADCW;
		
}