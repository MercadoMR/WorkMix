	;.include "m48def.inc"
	.def temp = r16
	.def temp2 = r18
	.cseg
	.org 0


	ldi temp,$0f ;load inmediate 
	ldi temp2,$0E
	ldi r17,$01 
	add temp,r17
	; out portb,temp  *** Cuando se incluyen definiciones se utiliza portb 
	; out $05, temp  *** De lo contrario utilizar direccion absoluta
	out $05,temp
	
	;Direccionamiento directo
	sts $000F,temp2;Guardar directamente en el registro 15 el valor E:dire <- registro
	;Guardarn en la posicion 34 de la memoria de datos (seccion I/0) el valor E
	sts $0022,temp2
	;Guardar en la posicion 288 de la memoria de datos (seccion RAM) el valor E
	sts $0120,temp2
	nop