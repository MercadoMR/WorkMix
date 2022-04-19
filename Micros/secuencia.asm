	.include "m48def.inc"
	.def temp=r16
	.def reg_conti=r17
	.cseg
	;**Interrupciones
	.org 0
	rjmp reset

	.org $000e
	rjmp cont_int

reset:
	ldi temp,$01
	out ddrb,temp
	ldi reg_conti,$00
	;***Configuracion del timer
	;**Modo CTC
	ldi temp,$02
	out tccr0a,temp

	ldi temp,$05  ;Preescalador a 1024
	out tccr0b,temp
	ldi temp,195 ;Cargar para contar hasta 195
	out ocr0a,temp
	ldi temp,$02
	sts timsk0,temp ; Habilitar la interrupcion por comparacion
	sei

main: nop ;En el lazo principal no se hace nada
	nop
	rjmp main


;*******Interrupcion de comparacion
cont_int: inc reg_conti
	cpi reg_conti,$05 ;Pregutnar igual 5
	breq toggle
	reti ;regresar de la interrupcion

toggle:ldi reg_conti,$00
	com temp ;Para cambiar la salida entre 0 o 1
	andi temp,$01 ; Solo nos importa el bit b0
	out portb,temp
	reti ;Se usa reti porque aun esta dentro de la interrupcion