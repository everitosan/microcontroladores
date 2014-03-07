#include <avr/io.h>
#include <util/delay.h>

const unsigned char tabla[10] = {	0x3f, 0x06, 0x5b,
									0x4f, 0x66, 0x6d,
									0x7d, 0x07, 0x7f, 0x67 };
unsigned char i = 0;
unsigned char asc = 1;

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	
    while(1)
    {
        PORTB = tabla[i];
		if(asc == 0)
		{	i--;
			if(i == 0)
				asc = 1;
		}		
		else
		{	i++;
			if(i == 9)
				asc = 0;
		}		
		_delay_ms(150);
    }
}