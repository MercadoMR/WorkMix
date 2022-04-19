
.include "m48def.inc"
.def temp=r16
.cseg
.org 0

rjmp reset 

.org $010
rjmp timer_0

reset:
	ldi temp,$01
	out ddrb,temp
	out tccr0b,temp
	;habilitar inst sobreflujo en registro extendido
	sts timsk0,temp
	out portb,temp 
	sei 
main:nop
	rjmp main
	;**** Interrupciones
timer_0:in temp,pinb
	com temp
	andi temp,$01
	out portb,temp
	reti