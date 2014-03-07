.include "m48def.inc"

.def a = R16
.def modo = R17
.def led = R18

.org 0000
ldi  a, low (ramend)
out spl, a
ldi a, high(ramend)
out sph, a

ldi modo, $FF
out ddrd, modo

ldi led, $01

ciclo: rol led
	   out portd, led
	   rcall tiempo
	   sbis portd, 7
	   rjmp ciclo

ciclo2: ror led
		out portd, led
		rcall tiempo
		sbis portd,0
		rjmp ciclo2
		rjmp ciclo

tiempo:	ldi R20, $00
loop2:	ldi R21, $00		
loop: 	dec R21
		brne loop		
		dec R20
		brne loop2
		ret
