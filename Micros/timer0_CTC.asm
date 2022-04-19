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
	;*** CONFIGURACION DE PINES
	;Salidas
	ldi temp,$01
	out ddrb,temp ;Salida en B0
	out ddrd,temp ;Salida en D0
	;Entradas
	ldi temp,$00
	out ddrc,temp ; Entradas en C0,C1,C2 y C3
	ldi temp,$0F
	out portc,temp ; Activar resistencias pull-up 
	;*************
	ldi reg_conti,$00

main: 
	in temp,pinc
	andi temp,$0F
	cpi temp,$0E
	breq sec
	rjmp incorrecto 
	rjmp main

sec:
	rcall delay_500ms
	in temp,pinc
	andi temp,$0F
	cpi temp,$0D
	breq sec2
	rjmp incorrecto

sec2:
rcall delay_500ms
	in temp,pinc
	andi temp,$0F
	cpi temp,$0B
	breq sec3
	rjmp incorrecto


sec3:
rcall delay_500ms
	in temp,pinc
	andi temp,$0F
	cpi temp,$07
	breq correcto
	rjmp incorrecto

incorrecto:
	;*** CONFIGURACION DEL TIMER
	;**Modo CTC
	ldi temp,$02
	out tccr0a,temp ;** Limpiar en comparacion

	ldi temp,$03  ;Preescalador a 64
	out tccr0b,temp
	ldi temp,78 ;Cargar para contar hasta 78
	out ocr0a,temp

	ldi temp,$02
	sts timsk0,temp ; Habilitar la interrupcion por comparacion con OCR0A
	sei ;Poner bit de interrupción
	;;
	out portd,$00
	rjmp main

correcto:
	;*** CONFIGURACION DEL TIMER
	;**Modo CTC
	ldi temp,$02
	out tccr0a,temp ;** Limpiar en comparacion

	ldi temp,$03  ;Preescalador a 64
	out tccr0b,temp
	ldi temp,8 ;Cargar para contar hasta 8
	out ocr0a,temp

	ldi temp,$02
	sts timsk0,temp ; Habilitar la interrupcion por comparacion con OCR0A
	sei ;Poner bit de interrupción
	rjmp main

;**** Subrutina
delay_500ms: ldi cont2, 200
	lazo2:	ldi cont1, 250 
	lazo1:	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec cont1  
	brne lazo1 
	dec cont2
	brne lazo2 
	ret


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