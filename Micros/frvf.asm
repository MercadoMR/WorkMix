	.include "m48def.inc"
	.def temp = r16
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
	;;ADMUX cargar e0
	ldi temp,$e0
	sts admux,temp ; Sólo cambió el admux
	;;Modo autodisparo Free Running 
	;;Quitar buffer digital ya que se usara como entrada analogica
	ldi temp,$01
	sts didr0,temp
	;;Preescalador a 8
	;;
	ldi temp,$EB
	sts adcsra,temp
	sei 

main:nop
	rjmp main


fin_conv: lds temp,adch ;;Cargar valor convertido
	out portb,temp ;;***Mandar a puerto b valor convertido
	reti 



