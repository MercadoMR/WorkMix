	.include "m48def.inc"
	.def temp = r16
	.def cte= r17
	.def cont1 = r18
	.def cont2 = r19
	.def tope = r20
	.cseg
	.org 0
	
	ldi temp,$03 ;Pin B0 para aumento y B1 para disminuir
	out portb,temp ;Activar resistencias pull-up
	ldi temp,$40 ;Pin D6 como salida 
	out ddrd,temp
	;Bits de configuracion a aplicar
	ldi temp,$83  ; COM0A1 poner 10 y WGM01 Y WGM00 A 11 (Fast PWM)
	out tccr0a,temp 
	ldi temp,$01 
	out tccr0b,temp ;Preescalador A 1
	;Numero a comparar
	ldi temp,50 ;Comenzar en 50
	out ocr0a,temp 
	ldi cte,$05 ;Aumentos de cinco en cinco

main: 
    in temp,pinb ;Leer pines B0 y B1
	andi temp,$03 ;Limpiar entrada
	cpi temp, $02 ;Se leyo B0 (Aumento)
	breq incrementar
	cpi temp, $01 ;Se leyo B1 (Decremento)
	breq decrementar
	rjmp main

incrementar: rcall delay_100ms 
	in temp,ocr0a
	ldi tope,$FF ; Cargar el valor maximo que podemos poner
	cpse temp, tope ; Si llego a tope no hacer la siguiente instruccion
	add temp,cte
	out ocr0a,temp
	rjmp main

decrementar: rcall delay_100ms 
	in temp,ocr0a
	ldi tope,$00 ; Cargar el valor minimo que podemos poner
	cpse temp, tope ; Si llego a tope no hacer la siguiente instruccion
	sub temp,cte
	out ocr0a,temp
	rjmp main

;Para observar los incrementos y esperar a que el registro de comp se actualice
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
