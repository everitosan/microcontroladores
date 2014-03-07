
;			   Contador		
;********************************************************************
;El registro 20 se utilizará como un contador decimal que se mostrará
;en el display de 7 segmentos.
;********************************************************************

	list p=16f876, f=INHX8M, r=hex
	include "p16f876.inc"
	include "macros.inc"

Conta		equ	20

			org	0

			Banco1						;Selecciona banco 1.
			clrf		TRISB				;Programa puerto B como salidas.
			Banco0						;Selecciona banco 0.

UNO:		clrf		Conta				;Inicializa el contador.

DOS:		movf		Conta,W
			andlw		b'00001111'		;Borra cuarteto de mayor peso.
			call		COD				;Visualiza en display.
			movwf		PORTB				;Visualiza.
			call		R1S				;Temporiza 1 segundo.
			incf		Conta,F			;Incrementa contador.
			movlw		0A					;¿Conta es igual a 0A?
			xorwf		Conta,W			;          "
			btfsc		STATUS,Z			;	   "
			goto		UNO				;Sí: pone "CONTA a cero.
			goto		DOS				;No: continúa el contador.


;********************************************************************
;			"COD"
;Esta rutina se encarga de localizar, según la cantidad de Conta, el
;código de 7 segmentos.
;********************************************************************


COD:		addwf		PCL,F				;Suma desplazamiento para localizar código.
			retlw		b'00111111'		;0
			retlw		b'00000110'		;1
			retlw		b'01011011'		;2
			retlw		b'01001111'		;3
			retlw		b'01100110'		;4
			retlw		b'01101101'		;5
			retlw		b'01111101'		;6
			retlw		b'00000111'		;7
			retlw		b'01111111'		;8
			retlw		b'01100111'		;9
			retlw		b'01110111'		;A
			retlw		b'01111100'		;B
			retlw		b'00111001'		;C
			retlw		b'01011110'		;D
			retlw		b'01111001'		;E
			retlw		b'01110001'		;F	

			include "retardos.inc"

		end


;				B0			 Hexa  	B7 B6 B5 B4 B3 B2 B1 B0  Nº Visualizado
;			-------		------------------------------------------------
;	     !	    !			3F 	 0  0  1  1  1  1  1  1		0
;	  B5 !	    ! B1		06		 0  0  0  0  0  1  1  0		1
;	     !	B6  !			5B		 0  1  0  1  1  0  1  1		2
;	      -------			4F		 0  1  0  0  1  1  1  1		3
;	     ! 	    !			66		 0  1  1  0  0  1  1  0		4
;	  B4 !	    ! B2		6D		 0  1  1  0  1  1  0  1		5
;	     !       !			7D		 0  1  1  1  1  1  0  1		6
;	      -------			07		 0  0  0  0  0  1  1  1		7
;			  B3				7F		 0  1  1  1  1  1  1  1		8
;								6F		 0  1  1  0  1  1  1  1		9
