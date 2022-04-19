	.include "m48def.inc"
	.def temp=r16
	.def cont1=r17
	.def cont2=r18
	.def cont3=r19
	.def cont4=r20
	.def cont5=r21
	.cseg
	.org 0
	
	rjmp reset ;Direccion 0 del vector de interrupciones
	rjmp interr0 ;Direccion 1

;CONFIG REG MASCARAS Y QUE tipo de flanco SE QUIERE DETECTAR

;PD2(INT0)

reset: 
	ldi temp, $80 ; Poner como Salida 
	out ddrb, temp
	ldi temp, $04 
	out portd, temp 
;eicra
;01 Cambio en el nivel lógico
	ldi temp,$01
	sts eicra,temp
;eimsk external int. mask register
	out eimsk,temp
	sei 
	ldi temp,$80
	out portb,temp

main: rcall delay_5s
	cbi portb,7
	nop
	rjmp main


;*****Interrupciones
interr0: rcall delay_15ms; Esperar por rebotes
	in temp, pind
	andi temp,$04 ;Si el pin esta en 0 el resultado sera 0 
	breq encender
	ldi temp,$01
	out eifr,temp ;Limpiar bandera por rebotes
	reti ;No hacer nada y regresar si no está en 0

encender: 
	sbi portb,7
	ldi cont3, 10
	ldi cont2, 200
  	ldi cont1, 250
	ldi temp,$01
	out eifr,temp ;Limpiar bandera por rebotes
	reti 

;***Subrutinas

delay_5s: ldi cont3, 10
lazo3:	ldi cont2, 200
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
	dec cont3
	brne lazo3
	ret

delay_15ms: ldi cont5, 6
lazo5:	ldi cont4, 250
lazo4:	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec cont4
	brne lazo4
	dec cont5
	brne lazo5
	ret