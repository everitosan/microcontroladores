/*
 * Ejemplo8_ADC.c
 *
 * Created: 05/03/2013 01:19:51 p. m.
 *  Author: Everardo
 */ 


#include <avr/io.h>
#include <util/delay.h>

void ADC_init();
int read_adc(char canal);

int res;

int main(void)
{
	ADC_init();
	DDRB=0xff;
	
    while(1)
    {
		res=read_adc(2);	
		if(res<128)
			PORTB=0x01;
				else if(res<256)
				PORTB = 0x03;
					else if(res<384)
					PORTB=0x07;
						else if(res<512)
						PORTB=0x0f;
							else if(res<640)
							PORTB=0x1f;
								else if(res<768)
								PORTB=0x3f;
									else if(res<869)
									PORTB=0x7f;
										else
										PORTB=0xff;
										
		_delay_ms(35);
    }
}

void ADC_init()
{
	
	ADMUX=0x40;
	ADCSRA=0x80;
	
	
}

int read_adc(char canal)
{
	ADMUX=(ADMUX&0XF0)|canal; //selecion canal
	ADCSRA= ADCSRA|(1<<ADSC); //inicia conv
	
	while((ADCSRA&(1<<4))==0); //espera a que se completa la conversion
	return ADCW;
 }