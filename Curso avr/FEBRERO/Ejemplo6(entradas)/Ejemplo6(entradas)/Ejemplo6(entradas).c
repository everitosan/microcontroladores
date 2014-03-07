/*
 * Ejemplo6_entradas_.c
 *
 * Created: 27/02/2013 01:28:26 p. m.
 *  Author: Everardo
 */ 


#include <avr/io.h>

int main(void)
{
	DDRB=0xff;	
	DDRD=0x00;
	PORTD=0XFF;//ACTIVAR RESISTENCIA DE PULL-UP	
	
    while(1)
    {
        PORTB=PIND;
    }
}