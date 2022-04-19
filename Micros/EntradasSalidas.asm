	.include "m48def.inc"
	.def temp = r16
	.cseg
	.org 0

	ldi temp, $01
;**Registros IO
	out portc,temp ;**Habilita resistencia pull off
	out ddrd,temp ;**Pone pin como salida 
main:in temp,pinc
	com temp ;Hace complemento a 1 de temp
	out portd, temp
	rjmp main
