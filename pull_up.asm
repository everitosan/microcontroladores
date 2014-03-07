.include "m48def.inc"

	.def a =R16
	.def entrada =R18

	.org 0000
	ldi a, low (ramend)
	out spl, a
	ldi a, high (ramend)
	out sph, a
	
	ldi R17, $FF
	out ddrd, R17; puerto de como salida

	com R17 ;R17 = 0b00000000, $00
	out portd, R17 ; apagamos los puertos de salida
	out ddrc, R17 ; puertoc como entrada

	com R17 ; R17 = 0b11111111, $ff
	out portc, R17 ; activamos oull up



	get_c: in entrada, pinc ;obtenemos el pinc en el registro entrada
			ori entrada, 0b11000000 ; 
			com entrada
			out portd, entrada
			rjmp get_c
