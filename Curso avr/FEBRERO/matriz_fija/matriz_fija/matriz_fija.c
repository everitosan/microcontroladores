/*
 * matriz_fija.c
 *
 * Created: 22/02/2013 01:50:00 p.m.
 *  Author: Israel
 */ 


#include <avr/io.h>
#include <util/delay.h>

const unsigned char mensaje[5][9]={{0x00,0xff,0xff,0xff,0x18,0x18,0xff,0xff,0xff},
								  {0x00,0xff,0xff,0xff,0xe7,0xe7,0xff,0xff,0xff},
							      {0x00,0xff,0xff,0xff,0x03,0x03,0x03,0x03,0x03},
							      {0x00,0xff,0xff,0xff,0xc4,0xc4,0xff,0xff,0xff},
								  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
									 
unsigned char col_mensaje;								 
unsigned int duracion;
unsigned char col;
unsigned char letra;								 
unsigned char copia[8];	
unsigned char k=0;						 

int main(void)
{	DDRB=0xff;
	DDRD=0xff;
	PORTD=0x80;// activada 1ra col
	
	
    while(1)
    {	for(k=0;k<8;k++)// ciclo de copiado
		{	if(k==7)
			copia[k]=mensaje[letra][col_mensaje];
			else	
				copia[k]=copia[k+1];
		}			
        
		for(duracion=0;duracion<15;duracion++)// duracion
		{	
			for(col=0;col<8;col++)//barrido de columnas
			{	PORTB=~copia[col];
				_delay_ms(1);
				PORTD=PORTD>>1;
			}
			PORTD=0x80;// volver a la primera col
		}	
		col_mensaje++;
		if(col_mensaje==9)
		{	col_mensaje=0;
			letra++;
			if(letra==5)
				letra=0;
		}					
    }
}