.include "m8def.inc"

	.def aux=R18
	.def cont=R21
	.def a= R16

	.org 0000
	ldi  a, low (ramend)
	out spl, a
	ldi a, high(ramend)
	out sph, a

	;inicializacion de apuntadores	
	clr zl
	ldi zh, $01;apuntador z en $0100
	ldi xl, $50
	ldi xh, $01; apuntador x en $0150

	ldi cont, $0;inicializacion del contador

	ldi R17, $FF ; modo de salida del puerto
	out ddrd, R17 ;inicializacion del puerto como salida

	ciclo:	 st z, cont
			 ld aux, z
			 st x+, aux
			 out portd, cont
			 inc zl
			 inc cont
			 cpi cont, $15 
			 brne ciclo

	

	fin: rjmp fin

								
	 
