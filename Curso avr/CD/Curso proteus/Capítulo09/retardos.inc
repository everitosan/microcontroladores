
;********************************************************************
;CONJUNTO DE SUBRUTINAS QUE PUEDEN INCLUIRSE EN OTROS PROGRAMAS CON
;LA ORDEN include "retardos.inc"
;Se dispone de retardos de 100 microseg., 1 ms, 5 ms, 10 ms, 20 ms,
;100 ms y 1 s, y las más largas tratan el WDT.
;********************************************************************

	CBLOCK		0x63
	RET1, RET2, RET3
	ENDC

;************************************************************************
;       		 Cálculo del tiempo
;Para una Fclock = 4 MHz, Tclock = 0,25 microsegundos.
;Un ciclo de instrucción se ejecuta en 4 Tclock = 1 microsegundo (us).
;
;tsubrutina R100MI = (3.RET1 + 7) micseg.
;tsubrutina R1MS = (4.RET1 + 8) micseg.
;tsubrutina R5MS = (4.RET1.RET2 + 4.RET2 + 4) micseg.
;tsubrutina R10MS = (4.RET1.RET2 + 4.RET2 + 1) micseg.
;tsubrutina R20MS = (4.RET1.RET2 + 4.RET2 + 1) micseg.
;tsubrutina R100MS = (4.RET1.RET2 + 4.RET2 + 1) micseg.
;tsubrutina R1S = (4.RET1.RET2.RET3 + 4.RET2.RET3 + 4.RET3 + 5) micseg.
;************************************************************************

;********************************************************************
;			"R100MI"					
;Rutina de temporización 100 microsegundos.
;********************************************************************

R100MI	movlw		.31				;Carga RET1.
			movwf		RET1				;	"

R100MI1:	decfsz	RET1,F			;Decrementa RET1 hasta su valor 00h.
			goto		R100MI1			;Si RET1 no es cero repite decremento.
			nop							;Si RET1=0 ajusta tiempo y retorna.
			nop							;	"
			return

;********************************************************************
;			"R1MS"
;Rutina de temporización 1 milisegundo.
;********************************************************************

R1MS		movlw		.248				;Carga RET1.
			movwf		RET1				;	"

R1MS1:	clrwdt						;Borra WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R1MS1				;Si RET1 no es cero repite decremento.
			nop							;Si RET1=0 ajusta tiempo y retorna.
			nop							;	"
			nop							;	"
			return

;********************************************************************
;			"R5MS"
;Rutina de temporización 5 milisegundos.
;********************************************************************	

R5MS		movlw		.24				;Carga RET2.
			movwf		RET2				;	"

R5MS1:	movlw		.51				;Carga RET1.
			movwf		RET1				;	"

R5MS2:	clrwdt						;Inicializa WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R5MS2				;Si RET1 no es cero repite decremento.
			decfsz	RET2,F			;Si RET1=0 decrementa RET2.
			goto		R5MS1				;Si RET2 no es 0 repite el bucle.
			nop							;Si RET2=0 ajusta tiempo y retorna.
			nop							;	"
			nop							;	"
			return

;********************************************************************
;			"R10MS"
;Rutina de temporización 10 milisegundos.
;********************************************************************

R10MS		movlw		.25				;Carga RET2.
			movwf		RET2				;	"

R10MS1:	movlw		.99				;Carga RET1.
			movwf		RET1				;	"

R10MS2:	clrwdt						;Inicializa WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R10MS2			;Si RET1 no es cero repite decremento.
			decfsz	RET2,F			;Si RET1=0 decrementa RET2.
			goto		R10MS1			;Si RET2 no es 0 repite el bucle.
			return						;Si RET=0 retorna.

;********************************************************************
;			"R20MS"
;Rutina de temporización 20 milisegundos.
;********************************************************************

R20MS		movlw		.25				;Carga RET2.
			movwf		RET2				;	"

R20MS1:	movlw		.199				;Carga RET1.
			movwf		RET1				;	"

R20MS2:	clrwdt						;Inicializa WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R20MS2			;Si RET1 no es cero repite decremento.
			decfsz	RET2,F			;Si RET1=0 decrementa RET2.
			goto		R20MS1			;Si RET2 no es 0 repite el bucle.
			return

;********************************************************************
;			"R100MS"
;Rutina de temporización 100 milisegundos.
;********************************************************************

R100MS	movlw		.100				;Carga RET2.
			movwf		RET2				;	"

R100MS1:	movlw		.249				;Carga RET1.
			movwf		RET1				;	"

R100MS2:	clrwdt						;Inicializa WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R100MS2			;Si RET1 no es cero repite decremento.
			decfsz	RET2,F			;Si RET1=0 decrementa RET2.
			goto		R100MS1			;Si RET2 no es 0 repite el bucle.
			return

;********************************************************************
;			"R1S"
;Rutina de temporización 1 segundo.
;********************************************************************

R1S		movlw		.250				;Carga RET3.
			movwf		RET3				;	"
	
R1S1:		movlw		.100				;Carga RET2.
			movwf		RET2				;	"

R1S2:		movlw		9					;Carga RET1.
			movwf		RET1				;	"

R1S3:		clrwdt						;Inicializa WDT.
			decfsz	RET1,F			;Decrementa RET1 hasta cero.
			goto		R1S3				;Si RET1 no es cero repite decremento.
			decfsz	RET2,F			;Si RET1=0 decrementa RET2.
			goto		R1S2				;Si RET2 no es 0 repite el bucle 2.
			decfsz	RET3,F			;Si RET2=0 decrementa RET3.
			goto		R1S1				;Si RET3 no es 0 repite el bucle 3.
			return

;********************************************************************
;	CBLOCK	dirección o etiqueta
;	variables
;	ENDC
;Ejemplo:
;	CBLOCK	0x40
;	RET1, RET2, RET3
;	ENDC
;Se asignará la dirección 40h a RET1, la 41h a RET2 y la 43h a RET3.
;Se conseguirá lo mismo así:
;	CBLOCK	variables
;	RET1, RET2, RET3
;	ENDC
;	Y en el programa principal asignamos:
;	variables equ	40
;********************************************************************

