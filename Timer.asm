.include "m8def.inc"

.def a =R16
.def b= R17
.def modo =R18
.equ led =0

	

	.org 0000
	rjmp inicio

	.org $000D
	ldi a, high(65536-9804)
	out TCNT1H, a
	ldi a, low (65536-9804)
	out TCNT1L, a
	sbic portd, led
	rjmp apaga

	enciende:	sbic portd, led
				reti

	apaga:		cbi portd, led
				reti



inicio:
		ldi modo, $ff
		out ddrd, modo
		ldi a, high (65536-9804)
		out TCNT1H, a
		ldi a, low (65536-9804)
		out TCNT1L, a
	
		ldi a, $05
		out TCCR1B, a
		ldi a, 1<< TOIE1
		out TIMSK, a
		sei

		fin:rjmp fin
