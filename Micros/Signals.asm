	.include "m48Pdef.inc"
	.def temp = r16
	.def leido = r17
	.def cont1 = r18
	.def cont2 = r19
	.cseg
	.org $0000
	rjmp RESET
	.org $0012
	rjmp USART_RX

RESET:
	ldi temp,$00
	out portb,temp
	ldi temp,$40 ;Pin D6 como salida 
	out ddrd,temp
	rcall cfg_PWM
	rcall cfg_USART
	sei ;Activar interrupción
	rjmp main

main: nop
	rjmp main

USART_RX:
	lds leido,udr0 ;Leer con lds porque es extendido
	rcall brillo
	mov temp,leido
	andi temp,$0F
	out portb,temp
reti

brillo:
	mov temp,leido
	andi temp,$F0
	ldi cont1,$11 ;Cargar 17, incrementos de 17 en diecisiete
	swap temp ;Cambiar nibbles
	mul temp,cont1 ;Multiplicar entrada con 17
	mov temp,r0 ;Copiar multiplicacion
	out ocr0a,temp
	rcall delay_100ms
ret

;***************************************************************************
;						RUTINAS DE CONFIGURACION
;***************************************************************************

cfg_PWM:
	ldi temp,$83  ; COM0A1 poner 10 y WGM01 Y WGM00 A 11 (Fast PWM)
	out tccr0a,temp 
	ldi temp,$01 
	out tccr0b,temp ;Preescalador A 1
	;Numero a comparar
	ldi temp,50 ;Comenzar en 50
	out ocr0a,temp 
ret

cfg_USART:
	;Poner BAUD RATE
	ldi temp,$00
	sts UBRR0H,temp
	ldi temp, 12 ;12 (1MHz) 103 (8MHz) 207 (16MHz)
	sts UBRR0L,temp
	;Velocidad doble
	ldi temp,$22
	sts UCSR0A,temp 
	;Activar Recepcion y Interrupcion de recepcion
	ldi temp, (1<<RXCIE0) |(1<<RXEN0)
	sts UCSR0B, temp
	;Formato de la trama
	ldi temp, (1 << UCSZ01) | (1 << UCSZ00)
	sts UCSR0C, temp
ret

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
