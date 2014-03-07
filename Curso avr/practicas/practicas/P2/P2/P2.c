/*
 * P2.c
 *
 * Created: 28/08/2012 02:04:40 p.m.
 *  Author: israel
 */ 


#include <avr/io.h>
#include <util/delay.h>
unsigned char var;

int main(void)
{
	DDRB	= 0b11111111;
	PORTB	= 0b00000000;
	var = 0x01;
	
    while(1)
    {
		if(var == 0b00000000)
			var = 0b00000001;
		_delay_ms(250);		
		PORTB = var;
		var = var << 1;	
    }
}