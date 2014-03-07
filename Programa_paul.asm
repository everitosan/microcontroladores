/*
 * efectos.asm
 *
 *  Created: 27/02/2014 07:57:40 p.m.
 *   Author: Paul
 */ 

.include"m8def.inc"
.def a=r16 
.def b=r17 
.def c=r18 
.def h=r22 
.def g=r23
.def d=r19 
.def e=r20 
.def f=r21 
.def i=r24

	.org 0000
	ldi a,low(ramend)
	out spl,a
	ldi a,high(ramend)
	out sph,a

;config del portd como salida
	ldi a,$ff
	out ddrd,a
	clr a
	out portd,a
;config del portc como entrada
	ldi a,$00
	out ddrc,a
	com a
	out portc,a

	ldi b,$ff
	ldi c,$0f
	ldi d,$f0
	ldi e,$01
	ldi f,$50
	ldi h,$cc
	ldi i,$00
apagados:ldi g,$00

pregunta:
		in a,pinc ;00111110
		ori r16,0b11000000  ;11000000-->11111110 con el com
		com a     ;00000001
			cpi r16,$00
			breq pregunta
			cpi r16,$01
			breq efecto1
			;rjmp efecto1
			cpi r16,$02
			breq efecto2
			;rjmp efecto2
			cpi r16,$04
			breq efecto3
			;rjmp efecto3
			cpi r16,$8
			breq efecto4
			;rjmp efecto4
			cpi r16,$10
			breq efecto5
			;rjmp efecto5
			cpi r16,$20
			breq efecto6
			;rjmp efecto6
			rjmp pregunta
		efecto1:out portd,b
				;rcall tiempo
				com b
				out portd,b
				;rcall tiempo 
				com b
				out portd,b

				sbic pinc,0
				rjmp apagados
				rjmp pregunta
		efecto2:out portd,c
				rcall tiempo
				out portd,d
				rcall tiempo
				com d
				
				sbic pinc,0
				rjmp apagados
				rjmp pregunta
		efecto3:out portd,e
				rcall tiempo
				rol e
				out portd,e
				
				sbic portd,7
				rjmp efecto3
				sbic pinc,0
				rjmp apagados
				rjmp pregunta

		efecto4:out portd,f
				rcall tiempo
				ror f
				out portd,f

				sbic portd,0
				rjmp efecto4

				sbic pinc,0
				rjmp apagados
				rjmp pregunta
		efecto5:out portd,h
				rcall tiempo
				com h

				sbic pinc,0
				rjmp apagados
				rjmp pregunta
		efecto6:clr r24
					out portd,r24
					rcall tiempo
					ser r24
					out portd,r24
					rcall tiempo
					rjmp pregunta

		.org $300
		tiempo:ldi r25,$00
		loop1:ldi r26,$00
		loop2:dec r26
			  brne loop2
			  dec r25
			  brne loop1
			  ret
		fin:rjmp fin



