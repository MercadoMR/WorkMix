	.include "m48def.inc"
	.def temp=r16
	.cseg
	.org 0
	rjmp reset
	;Interrupción de recepcoón completa
	.org $012
	rjmp recibe

reset:
	ldi temp,$02
	out ddrd,temp
	sts UCSR0A,temp;Velocidad de trans. al doble
	ldi temp,$98
	sts UCSR0B,temp 
	ldi temp,12

	sts ubrr0l,temp ; Transmitir a 9600 bps Parte baja l
	ldi temp,$01
	mov r15, temp
	sei

main:nop
	rjmp main

recibe: lds temp,udr0 ;Leer con lds porque es extendido
	add temp,r15 ; agregar
	sts udr0,temp ;Sumar uno al recibido?
	reti