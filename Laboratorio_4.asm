.include "m48def.inc"
;.include "m8def.inc"

	.def a = R16
	.def led= R17
	.def entrada =R18

	.org 0000
	ldi a, low(ramend)
	out spl, a
	ldi a, high(ramend)
	out sph, a

	ldi led, $ff
	out ddrd, led

	ldi led, $00
	out portd, led

	;cbi ddrc, 0
	;sbi portc, 0
	out ddrc, led
	com led
	out portc, led

	ldi led, $01
	

	get_pin:rcall lee
			cpi entrada, $01
			breq gira_d
			cpi entrada, $02
			breq gira_i	 
			rjmp get_pin

	lee:	in entrada, pinc
			ori entrada, 0b11000000
			com entrada
		ret

	gira_d:	out portd, led
			rcall tiempo
			clc
			rol led
			sbic portd, 3
			ldi led, $01
			rjmp get_pin

	gira_i:	out portd, led
			rcall tiempo
			clc
			ror led
			sbic portd, 0
			ldi led, $08
			rjmp get_pin


	tiempo: ldi R21, $aa
		loop:ldi R20, $aa
		loop2:dec R20
			brne loop2
			dec R21
			brne loop
			ret
