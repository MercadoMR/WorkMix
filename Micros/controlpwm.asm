	.include "m48def.inc"
	.def temp = r16
	.def cte= r17
	.def cont1 = r18
	.def cont2 = r19
	.cseg
	.org 0
	
	ldi temp,$01
	out portb,temp
	ldi temp,$40 ;pin d6 como salida 
	out ddrb,temp
	;Bits de configuracion a aplicar
	ldi temp,$83 
	out tccr0a,temp
	ldi temp,$01
	out tccr0b,temp
	;Numero a comparar
	ldi temp,127
	out ocr0a,temp
	ldi cte,$05

main: in temp,pinb
	andi temp,$01
	breq incrementar
	rjmp main

incrementar: ;rcall delay_100ms
	in temp,ocr0a
	add temp,cte
	out ocr0a,temp
	rjmp main


delay_100ms: ldi cont1,40
lazo2:	ldi cont2,250
lazo1:	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec cont2
	brne lazo1
	dec cont1
	brne lazo2
	ret



