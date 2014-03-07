/*
 * Ejemplo5.c
 *
 * Created: 01/03/2013 11:34:05 p. m.
 *  Author: Everardo
 */ 



#include <avr/io.h>
#include <util/delay.h>
//letra ! indice
const unsigned char mensaje[3][8]={{0x00,0x00,0xFF,0x7E,0x3C,0x18,0x00,0x00},//flecha
								   {0x00,0x00,0x18,0x3C,0x7E,0xFF,0x00,0x00},
								   {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};//flecha invertida
const unsigned char eve[6][8]={
								{0xFF,0xFF,0xDB,0xDB,0xDB,0xDB,0xDB,0x81},
								{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
								{0xF8,0xFC,0x06,0x03,0x03,0x06,0xFC,0xF8},
								{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
								{0xFF,0xFF,0xDB,0xDB,0xDB,0xDB,0xDB,0x81},
								{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
									 
unsigned char indice=0;								 
unsigned char i;
unsigned char letra=0;								 
unsigned char copia[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char k=0;						 

int main(void)
{	DDRB=0xff;
	DDRD=0xff;
	PORTD=0x80;// activada 1ra col
	
	
	while(1)
	{
		//for que copia y genera la nueva secuencia a mostrar
		for(i=0;i<8;i++)
		{
			if(i==7)
			copia[i]=mensaje[letra][indice];
			else
			copia[i]=copia[i+1];
			
		}

		//for que muestra
		for (i=0;i<10;i++)//numero de flasheos
		{
			for(k=0;k<8;k++)
			{
				PORTB=~copia[k];// manda los 8 bits de una columna
				_delay_ms(1);
				PORTD=PORTD>>1;//corrimiento del bit mas significatico, al bit mas significativo -1
			}
			PORTD=0x80;
		}

		// aumento del indice para mostrar una columna nueva for#1>else
		indice++;
		if(indice==8)//si indice ==8 no hay un valor en mensaje[letra][8]
		{
			indice=0;//regresamos el indice para copiar la nueva letra desde el incio
			letra++;//cambiamos a la siguiente letra
			if(letra==3)//si letra es ==2 no hay mensaje[2][x]
			{
				letra=0;
				while(letra<6)
				{
					for(i=0;i<16;i++)//duracion de eve (flash)
					{
						for (k=0;k<8;k++)
						{	//barrido de columnas
							PORTB=~eve[letra][k];
							_delay_ms(2);
							PORTD=PORTD>>1;
							copia[k]=0x00;
						}
						PORTD=0x80;
					}
					letra++;
				}
				letra=0;
				
				
			}
		}

	}
}