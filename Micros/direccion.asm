	.include "m48def.inc"
	.def temp = r16

	.cseg
	.org $0000
	rjmp RESET

RESET:
	ldi XL, LOW(datos)
	ldi XH, HIGH(datos)
	rjmp main

main: ldi temp, $16
	st X,temp
	ldi temp, $18
	st X+,temp
	ldi temp, $20
	st X,temp
	ldi temp, $21
	st X,temp
	rjmp main

	.dseg
	.org $0125 ; A partir de la direccion 0x0100
	datos: .byte 10 ;Reservar 10 espacios