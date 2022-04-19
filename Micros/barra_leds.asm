	.include "m48def.inc"
	.def temp=r16
	.def cont1= r17
	.def cont2=r18
	.cseg
	.org 0

	ldi temp,$00
	out	ddrc,temp
	ldi temp,$03
	;out ddrc, temp
	out portc, temp
	ldi temp,$ff
	out ddrb, temp ;pone los bits del puerto b a temp
	

main:	in temp,pinc 
	andi temp,$03
	cpi temp, $02 ; Resta con $02, Se presiono C0
	breq barra_asc
	cpi temp, $01
	breq barra_desc
	rjmp main

barra_asc: sbi portb,0
	rcall delay_125ms
	sbi portb,1
	rcall delay_125ms
	sbi portb,2
	rcall delay_125ms
	sbi portb,3
	rcall delay_125ms
	sbi portb,4
	rcall delay_125ms
	sbi portb,5
	rcall delay_125ms
	sbi portb,6
	rcall delay_125ms
	sbi portb,7
	rcall delay_125ms
	ldi temp,$00
	out portb, temp
	rcall delay_125ms

	rjmp main

barra_desc: sbi portb,7
	rcall delay_125ms
	sbi portb,6
	rcall delay_125ms
	sbi portb,5
	rcall delay_125ms
	sbi portb,4
	rcall delay_125ms
	sbi portb,3
	rcall delay_125ms
	sbi portb,2
	rcall delay_125ms
	sbi portb,1
	rcall delay_125ms
	sbi portb,0
	rcall delay_125ms
	ldi temp,$00
	out portb, temp
	rjmp main

;;*********** subrutinas
;Son dos ciclos el externo de 50 y el interno de 250 haciendo... ¿8 instrucciones?
delay_125ms: ldi cont2, 50
lazo2:	ldi cont1, 250
lazo1:	nop
	nop
	nop
	nop
	nop
	nop
	nop; siete cilcos reloj nops
	dec cont1 ; ciclo reloj 
	brne lazo1 ; dos ciclos
	dec cont2
	brne lazo2 ;
	ret
