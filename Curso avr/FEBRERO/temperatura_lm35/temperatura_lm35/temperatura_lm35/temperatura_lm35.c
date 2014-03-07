/*
 * temperatura_lm35.c
 *
 * Created: 06/03/2013 01:33:46 p.m.
 *  Author: Israel
 */ 


#include <avr/io.h>
#include "lcd.h"
#include <stdlib.h>
void ADC_init();
int READ_ADC(char canal);
int num; 
char arreglo[4];

int main(void)
{	DDRB=0x03;
	ADC_init();
	lcd_init();
	lcd_gotoxy(3,0);
	lcd_puts("TEMPERATURA");
    while(1)
    {
        num = READ_ADC(5);
		num= num/2.049; //guarda los grados
		
		itoa(num,arreglo,10);
		
		if(num>25)
			PORTB=0x02;
		else	if(num<21)
					PORTB=0x01;
					else
						PORTB=0x00;
		
		lcd_gotoxy(5,1);
		lcd_puts("       ");
		lcd_gotoxy(5,1);
		lcd_puts(arreglo);
		_delay_ms(400);
		
    }
}

void ADC_init()
{
	ADMUX=0x40;
	ADCSRA=0x80;
}
int READ_ADC(char canal)
{
	ADMUX=(ADMUX&0xf0)|canal; //selección canal
	ADCSRA=ADCSRA|(1<<ADSC);// inicia conv
	while((ADCSRA&(1<<4))==0);//espera a que se complete conv.
	return ADCW; // devuelve el res. de conv.
}