
// MANEJO DE PANTALLA LCD A 4BITS CONTROLADOR HD44780 O COMPATIBLE

#include "lcd.h"

//Inicializa LCD
void lcd_init(void)
{
	LCD_E_DIR_OUT;
	LCD_RS_DIR_OUT;
	LCD_RW_DIR_OUT;	
	
	LCD_E_LOW;
	LCD_RS_LOW;
	LCD_RW_LOW;	

		if (SALIDA==0)
			LCD_PORT_DIR&=0X0F;
		else
			LCD_PORT_DIR|=0XF0;
	
	delay_ms(45);
	lcd_nibble(LCD_RESET);
   	delay_ms(5);         
   	lcd_nibble(LCD_RESET); 
   	delay_ms(1);         
   	lcd_nibble(LCD_RESET); 
	delay_ms(1);         
		
		lcd_nibble(LCD_4BITS); 
   		delay_ms(1);         
   		lcd_nibble(LCD_4BITS); 
   		lcd_nibble(LCD_SET_4BITS); 
	   	
   	lcd_write(LCD_OFF_ON, 0);
   	lcd_write(LCD_CLEAR, 0);
   	lcd_write(LCD_ENTRY_MODE, 0);
	delay_ms(5);
}

void lcd_nibble(unsigned char nibble)
{
	LCD_RW_LOW;            
	
		if (SALIDA==0)
			LCD_PORT_DIR&=0X0F;
		else
			LCD_PORT_DIR|=0XF0;
		LCD_PORT_WRITE=(nibble&0xF0)|(LCD_PORT_WRITE&0x0F);
		
	delay_us(2);
	LCD_E_HIGH;
	delay_us(2);
	LCD_E_LOW;	
}

void lcd_write(char inst, char rs)
{
	while((lcd_read(0)==0x80));
	if (rs==0)
   		LCD_RS_LOW;
	else
		LCD_RS_HIGH;
   	delay_us(40);
   	lcd_nibble(inst);
	
   		lcd_nibble(inst<<4);

}

char lcd_read(char rs)
{
	char alto,bajo;   
  	if (rs==0)
   		LCD_RS_LOW;
	else
		LCD_RS_HIGH;
    LCD_RW_HIGH;
	
		if (ENTRADA==0)
			LCD_PORT_DIR&=0X0F;
		else
			LCD_PORT_DIR|=0XF0;			
		delay_us(2); 
	   	LCD_E_HIGH;  
	   	delay_us(2); 
	   	alto=LCD_PORT_READ;
	   	LCD_E_LOW;
	   	delay_us(2);
	   	LCD_E_HIGH;
	   	delay_us(2);
	   	bajo = LCD_PORT_READ;
	   	LCD_E_LOW;
		LCD_RW_LOW;
	   	return (alto&0xF0)|(bajo>>4);
	  	   	
}

void lcd_puts(const char * s)
{
	while(*s!=0)	
		lcd_write(*s++, 1);	
}

void lcd_gotoxy(char x, char y)
{
	if(y==0)
   		y = LCD_LINE1;
   	else
 	   	y = LCD_LINE2;
   	lcd_write(x+y, 0); 
}

void lcd_clear(void)
{
   lcd_write(LCD_CLEAR, 0);
}


