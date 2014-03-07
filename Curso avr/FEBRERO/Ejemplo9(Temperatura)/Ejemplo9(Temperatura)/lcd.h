
// MANEJO DE PANTALLA LCD A 4BITS CON CONTROLADOR HD44780 O COMPATIBLE

//////////////////////////////////////////////////////////
//DEFINICIONES DE PINES DE LA LCD						  

#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>




#define		BIT_0		0X01
#define		BIT_1		0X02
#define		BIT_2		0X04
#define		BIT_3		0X08
#define		BIT_4		0X10
#define		BIT_5		0X20
#define		BIT_6		0X40
#define		BIT_7		0X80

#define		SALIDA			1
#define		ENTRADA			0

#define		LCD_RS_DIR_IN		DDRD&=~BIT_1
#define		LCD_RW_DIR_IN		DDRD&=~BIT_2
#define		LCD_E_DIR_IN		DDRD&=~BIT_3

#define		LCD_RS_DIR_OUT		DDRD|=BIT_1
#define		LCD_RW_DIR_OUT		DDRD|=BIT_2
#define		LCD_E_DIR_OUT		DDRD|=BIT_3

#define		LCD_RS_LOW			PORTD&=~BIT_1
#define		LCD_RW_LOW			PORTD&=~BIT_2
#define		LCD_E_LOW			PORTD&=~BIT_3

#define		LCD_RS_HIGH			PORTD|=BIT_1
#define		LCD_RW_HIGH			PORTD|=BIT_2
#define		LCD_E_HIGH			PORTD|=BIT_3

#define		LCD_PORT_DIR	DDRD

#define		LCD_PORT_READ	PIND
#define		LCD_PORT_WRITE	PORTD

#define		delay_ms(x)		_delay_ms(x);//Cambiar segun el compilador
#define		delay_us(x)		_delay_us(x);//Cambiar segun el compilador

///////////////////////////////////////////

#define  LCD_CLEAR   	0x01   
#define  LCD_LINE1   	0x80   
#define  LCD_LINE2   	0xC0   
#define	 LCD_RESET	 	0X30   
#define	 LCD_SET_4BITS	0XC0	
 
#define  LCD_4BITS		0x20   
#define	 LCD_OFF_ON		0X0C	
#define	 LCD_ENTRY_MODE	0X06
////////////////////////////////////////////

void lcd_init(void);
void lcd_nibble(unsigned char nibble);
void lcd_write(char inst, char rs);
char lcd_read(char rs);
void lcd_puts(const char * s);
void lcd_gotoxy(char x, char y);
void lcd_clear(void);


