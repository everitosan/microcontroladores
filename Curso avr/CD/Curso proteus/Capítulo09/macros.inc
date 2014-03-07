;******************************************************************************
;Conjunto de macroinstrucciones que pueden ser utilizadas en cualquier programa.
;Deben incluirse el conjunto "macros.inc" al principio del programa.
;******************************************************************************

Banco0	macro
			bcf		STATUS,RP0
			bcf		STATUS,RP1
			endm

Banco1	macro
			bsf		STATUS,RP0
			bcf		STATUS,RP1
			endm

Banco2	macro
			bcf		STATUS,RP0
			bsf		STATUS,RP1
			endm

Banco3	macro
			bsf		STATUS,RP0
			bsf		STATUS,RP1
			endm
