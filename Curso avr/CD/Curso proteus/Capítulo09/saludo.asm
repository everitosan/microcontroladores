
;			    "saludo"
;********************************************************************
;Se trata de visualizar un pequeño rótulo, centrado en la fila superior,
;que ponga "HOLA".	
;********************************************************************

	list p=16f876,	f=INHX8M, r=hex
	include "p16f876.inc" 
	include "macros.inc"

			org	0
			goto	Inicio

			org	20

Inicio	Banco1						;Selecciona banco 1.
			movlw		06					;Configura las patillas del puerto A
			movwf		ADCON1			;como señales digitales.
			movlw		0xF8				;Programa PORTA: PA0, PA1 y PA2 salidas,
			movwf		TRISA				;resto como entradas
			movlw		00					;Programa PORTB como salida.
			movwf		TRISB				;	"
			Banco0						;Selecciona banco 0.
			movlw		01					;Envía orden de borrado de pantalla.
			call		ENVC				;	"
			movlw		06					;Programa modo de trabajo del visualizador:
			call		ENVC				;modo de cursor incremental y sin desplazamiento,
			movlw		0C					;visualizador ON, cursor oculto
			call		ENVC				;y sin intermitencia,
			movlw		38					;interface de 8 bits, 2 líneas y
			call		ENVC				;carácter de 5x7 puntos.
			movlw		86					;Coloca cursor en inicio de cartel.
			call		ENVC				;	"
			movlw		48					;Programa "H".
			call		ENVD				;	"
			movlw		6F					;Programa "o"
			call		ENVD				;	"
			movlw		6C					;Programa "l"
			call		ENVD				;	"
			movlw		61					;Programa "a"
			call		ENVD				;	"
	
Bucle:	goto		Bucle				;Final de programa.

			include "contlcd.inc"
			include "retardos.inc"

	end
