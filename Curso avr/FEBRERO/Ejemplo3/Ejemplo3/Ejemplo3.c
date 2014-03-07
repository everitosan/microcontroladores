/*
 * Ejemplo3.c
 *
 * Created: 20/02/2013 01:54:29 p. m.
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

unsigned char i=0,j=0;

int main(void)
{
	DDRB=0xff;
	DDRD=0xff;
	
    while(1)
    {
		/*
        for (j=0;j<10;j++)
        {	PORTD=tabla[j];
			for (i=0;i<10;i++)
			{
				PORTB=tabla[i];
				_delay_ms(500);
			}
			PORTD=tabla[j];
        }
		j=0;*/
		
		PORTB=tabla[i];
		PORTD=tabla[j];
		
		_delay_ms(500);
		i++;
		if(i==10)
		{	
			i=0;
			j++;
			if(j==10)			
			{
				j=0;
			}
		}
		
		
    }
}