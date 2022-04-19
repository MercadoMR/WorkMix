	.include "m48def.inc"
	.def temp = r16
	.def asc = r17

	.cseg
	.org 0
	rjmp RESET
	.org $010
	rjmp TIM0_OVF ;;Timer 0 Overflow Handler

;***************************************************************************
;		CICLO MAIN
;***************************************************************************
main: 
	sbis pinc, 2 ; Ignorar siguiente instruccion si C2 esta en 1
	com asc
	cpi asc, $01 ; Ver direccion del contador
	ldi temp,low(PC+7)
	push temp
	ldi temp,high(PC+5)
	push temp
condicion:	breq ar ; Si asc igual a 1, es ascendente
	rcall ab ; De lo contrario descendente
	rjmp main

ar: nop
  ret

ab: nop
  ret


iniciar:
  nop
  ret

;***************************************************************************
;		INTERRUPCIONES
;***************************************************************************

RESET:
	rcall iniciar ;Cargar constantes en memoria datos
	ldi temp,$01
	out tccr0b,temp ; Preescalador a 8 
	sts timsk0,temp ; Activar interrupcion de sobreflujo
	sei ;Activar interrupciones

	;	Configurar B0 a B7 como salida
	ldi temp, $FF
	out ddrb, temp
	;	Configurar C0 y C1 como salida, y C2 como entrada
	ldi temp, $03
	out ddrc, temp
	;	Resistencia pull-up en C2 y 1s en C0,C1
	ldi temp, $07
	out portc,temp

	ldi asc,$01 ;	Si esta en 1 el contador es ascendente
	rjmp main

TIM0_OVF: ldi temp,$07
	out portc, temp ; Apagar displays
	reti

