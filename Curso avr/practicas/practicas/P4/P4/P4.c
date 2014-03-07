/*
 * P4.c
 *
 * Created: 28/08/2012 02:36:52 p.m.
 *  Author: israel
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB = 0x00;
	PORTD = 0x01;
	
    while(1)
    {
		if(PIND == 0x01)
			PORTB = 0b00000001;
		_delay_ms(300);
		PORTB = PORTB << 1;
    }
}

//GRUPO: CURSO AVR ESIME CULHUACAN

