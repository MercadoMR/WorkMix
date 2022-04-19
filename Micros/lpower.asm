	.include "m48def.inc"
	.def temp=r16
	.def cont1=r17
	.def cont2=r18
	.def cont3=r19
	.def cont4=r20
	.def cont5=r21
	.cseg
	.org 0
	rjmp reset
	.org $04 ;PCINT1
	rjmp PCINT_1

RESET:
	ldi temp, $01
	out ddrb,temp
	out portc,temp
	;;Configuracion de interrupcion
	ldi temp, $02
	sts pcicr,temp
	ldi temp, $01
	sts pcmsk1, temp
	sei
	;;Configuracion modos sleep
	reti

PCINT_1: ;;Despertar
	rcall delay_20ms
	;Limpiar bandera
	ldi temp,$01
	out pcifr,temp
	reti

main:
	ldi temp,$01
	out portb,temp
	rcall delay_1s
	ldi temp,$05
	out smcr,temp
	sleep ;Al presionar el boton manda a pcint_1
	ldi temp,$00
	out portb,temp ;Apagar el led
	rcall delay_1s ;Esperar un segundo
	rjmp main 
	
delay_1s: ldi cont1,2
lazo3:	ldi cont2, 200
lazo2:	ldi cont3, 250
lazo1:	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec cont3
	brne lazo1
	dec cont2
	brne lazo2
	dec cont1
	brne lazo3
	ret

delay_20ms:ldi cont4,20
lazo5:	ldi cont5,250
lazo4:	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec cont5
	brne lazo4
	dec cont4
	brne lazo5
	ret