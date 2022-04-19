	.include "m48def.inc"
	.def temp = r16
	.def cont = r17
	.cseg 
	.org 0

	ldi temp,$00
	out eearh,temp
siguiente:	out eearl,temp
	out eedr,temp ; Escribir datos 
	ldi temp,$06
	sbi eecr,eempe ;Escribir uno a eempe
	sbi eecr,eepe	
	inc temp
lazo:	sbic eecr,eepe	
	rjmp lazo
	cpi temp,255
	breq salir
	rjmp siguiente

salir:nop
	rjmp salir