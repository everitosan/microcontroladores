.include "m48def.inc"

	.def a = R16
	.def modo = R17
	.def led = R19
	.def cont = R20
	.def prueba= R22
		
	.org 0000
	ldi a, low(ramend)
	out spl, a
	ldi a, high(ramend)
	out sph, a

	ldi modo, $01;modo de lectura de puerto
	out ddrc, modo; puerto c de entrdada
	ldi modo, $ff; modo de salida de puerto (ser modo)
	out ddrd, modo; puerto d de salida

	ldi cont, $00;contador empieza en 0
	ldi led, $ff
	    
		ldi prueba, $00
res: 	out portd, prueba
leepin: rcall obten_pin
		cpi R21, $00
		breq res
		cpi R21, 0b00000001
		breq sec1
		cpi R21, 0b00000010
		breq sec2
		cpi R21, 0b00000011
		breq sec3
		cpi R21, 0b00000100
		breq sec4
		cpi R21, 0b00000101
		breq sec5
		cpi R21, 0b00000110
		breq sec6
		out portd, prueba

	sec1:
		ldi cont, $01
		ciclo1:	out portd, cont
				rcall tiempo
				rol cont
				rcall obten_pin
				sbic portd, 7
				ldi cont, $01
				cpi R21, $01
				breq ciclo1
		rjmp leepin
	sec2:
		ldi cont, $01
		ldi modo, 0b10000000
		ciclo2:	rcall obten_pin
				cpi R21, $02
				brne leepin
				out portd, cont
				rcall tiempoh
				cp cont, modo
				rol cont
				brne ciclo2
				rjmp sec2
	sec3:
		;ldi cont, $01
		ldi modo, $FF
		ciclo3:	out portd, cont
				rcall tiempoh
				rol cont
				rcall obten_pin
				cpi R21, $03
				brne leepin
				cp cont, modo
				brne ciclo3
				subciclo3: 	ldi modo, $00
							out portd, cont	
							rcall tiempoh
							ror cont
							rcall obten_pin
							cpi R21, $03
							brne leepin
							cp cont, modo
							brne subciclo3
							rjmp sec3

	sec4:com led
		 out portd, led
		 rcall tiempo
	   	 rjmp leepin

	sec5:
		ldi cont, 0b00011111
		out portd, cont
		;rcall tiempo
		rjmp leepin
	sec6:
		ldi cont, 0b00111111
		out portd, cont
		;rcall tiempo
		rjmp leepin


tiempo:	ldi R23, $00
loop2:	ldi R24, $00		
loop: 	dec R24
		brne loop		
		dec R23
		brne loop2
		ret

tiempoh:ldi R23, $00
loop2h:ldi R21, $AA		
looph: 	dec R21
		brne looph
		dec R23
		brne loop2h		
		ret

obten_pin:in R21, pinc ; input del puerto c
		  andi R21, 0b00111111 ;enmascaramiento
		  ;ldi R21, $04
		  ret



