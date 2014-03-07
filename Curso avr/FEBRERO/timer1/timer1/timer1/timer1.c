/*
 * timer1.c
 *
 * Created: 11/03/2013 01:24:36 p.m.
 *  Author: Israel
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h> // itoa(,,)
#include "lcd.h"
int h=14,m=11,s=50;
char h_C[3];
char m_C[3];
char s_C[3];

int main(void)
{	DDRB=0xff;
	TCCR1A=0x00;
	TCNT1=65535-15625; // interrup cada 1 seg.
	TIMSK1=0x01;
	TCCR1B=0x03;
	
	lcd_init();
	lcd_gotoxy(4,0);
	lcd_puts("LA HORA ES:");
	
	itoa(h,h_C,10);
	itoa(m,m_C,10);
	itoa(s,s_C,10);
	
	lcd_gotoxy(5,1);
	lcd_puts(h_C);
	lcd_puts(":");
	lcd_puts(m_C);
	lcd_puts(":");
	lcd_puts(s_C);
	
	sei(); // activan interrupciones globales;
	
    while(1)
	{
		PORTB=~PORTB;
		_delay_ms(200);
	}
}

ISR(TIMER1_OVF_vect)
{	TCNT1=65535-15625; // interrp cada 1 seg.
	
	s++;
	if(s==60)
	{
		s=0;
		m++;
		if(m==60)
		{
			m=0;
			h++;
			if(h==24)
				h=0;
		}
	}
	
	itoa(h,h_C,10);
	itoa(m,m_C,10);
	itoa(s,s_C,10);
	
	lcd_gotoxy(5,1);
	if(h<10)
		lcd_puts("0");
	lcd_puts(h_C);
	lcd_puts(":");
	if(m<10)
		lcd_puts("0");
	lcd_puts(m_C);
	lcd_puts(":");
	if(s<10)
		lcd_puts("0");
	lcd_puts(s_C);
	
}

