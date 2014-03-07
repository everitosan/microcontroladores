/*
 * vumetro_5_mar.c
 *
 * Created: 05/03/2013 02:09:45 p.m.
 *  Author: Israel
 */ 


#include <avr/io.h>
#include <util/delay.h>
void ADC_init();
int READ_ADC(char canal);

int res;

int main(void)
{	ADC_init();
	DDRB=0xff;
    while(1)
    {	res=READ_ADC(2);
		if(res<9)
			PORTB=0x01;
		else if(res<18)
				PORTB=0x03;
			else if(res<27)
					PORTB=0x07;
				else if(res<36)
						PORTB=0x0f;
					else if(res<45)
							PORTB=0x1f;
						else if(res<54)
								PORTB=0x3f;
							else if(res<63)
									PORTB=0x7f;
								else if(res<70)
										PORTB=0xff;
			_delay_ms(35);														
         
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