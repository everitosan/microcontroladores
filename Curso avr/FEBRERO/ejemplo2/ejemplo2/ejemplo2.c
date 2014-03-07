/*
 * ejemplo2.c
 *
 * Created: 20/02/2013 01:27:06 p. m.
 *  Author: Everardo
 */ 


#include <avr/io.h>
#include <util/delay.h>


unsigned char tabla[]={
				0x3f,
				0x06,
				0x5b,
				0x4f,
				0x66,
				0x6d,
				0x7d,
				0x07,
				0x7f,
				0x67
				};
unsigned char i=0;

int main(void)
{
	DDRB=0xff;
		
    while(1)
    {
        for(i=0; i<10;i++)
		{
			PORTB=tabla[i];		
			_delay_ms(1000);
		}			
		
		i=0;
		
    }
}