;;Modo single, el valor no cambia hasta presionar un botón
	.include "m48def.inc"
	.def temp = r16
	.def cont1 = r17
	.def cont2 = r18
	.cseg 
	.org 0
	;;Conectar terminal 20 a Vcc 
	;;***Interrupción fin de conversión
	rjmp reset 
	
	.org $015
	rjmp fin_conv
	;Cuando termine la conversion se muestra el valor en binario
reset:	;;***CONFIGURACION PONES
	ldi temp,$ff
	out ddrb,temp
	;;ADMUX cargar 60
	ldi temp,$60
	sts admux,temp 
	;;Quitar buffer digital ya que se usara como entrada analogica
	ldi temp,$01
	sts didr0,temp
	;;Preescalador a 8
	;;
	ldi temp,$CB
	sts adcsra,temp
	sei 

main:sbic pinc,1
	rjmp main
	rcall delay_15ms ;;Quitar rebotes
	;;Iniciar conversión
	ldi temp,$CB
	sts adcsra,temp
	rjmp main

fin_conv: lds temp,adch ;;Cargar valor convertido
	out portb,temp ;;***Mandar a puerto b valor convertido
	reti 

delay_15ms: ldi cont1,6
lazo2:	ldi cont2, 250
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
	 


