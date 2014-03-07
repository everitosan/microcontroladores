/*
 * Ejemplo1.c
 *
 * Created: 19/02/2013 10:57:11 p. m.
 *  Author: Everardo
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRB=0Xff;
	PORTB=0x01;
    while(1)
    {
        while(PORTB!=0x80)
		{
			PORTB=PORTB<<1;
			_delay_ms(300);
		}		 
		while(PORTB!=0x01)
		{
			PORTB=PORTB>>1;
			_delay_ms(300);			
		}
    }
}