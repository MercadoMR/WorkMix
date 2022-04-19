/*
 * resp.asm
 *
 *  Created: 20/01/2021 09:22:48 p. m.
 *   Author: MIMR

  .include "m328Pdef.inc"
 .def temp = r16
 .def cont1 = r17
 .def cont2 = r18
 .def caracter = r19
 .def cursor = r20
 .def boomer = r21

 ; PD7-PD4 -> D7-D4 | PD3 -> E | PD2 -> RS

 .cseg
 .org $0000
 rjmp RESET

.macro escribir_caracter
	;****** ESCRITURA DE CARACTERES
	;Envio de los MSB
	ldi temp,$F0
	and temp,@0   ; Copiar los 4 MSB
	ori temp,$0C  ; E = 1 , RS = 1 
	out portd,temp
	andi temp,$F4 ; E = 0 , RS = 1
	out portd,temp
	rcall delay_50us
	;Envio de los LSB
	ldi temp,$0F
	and temp,@0   ; Copiar los 4 LSB
	swap temp	  ; Cambiar de posicion los bits
	nop
	ori temp,$0C  ; E = 1 , RS = 1
	out portd,temp
	andi temp,$F4 ; E = 0 , RS = 1
	out portd,temp
	rcall delay_50us
.endmacro

RESET:
	ldi temp,$FE ;PD0 como entrada, los demas salida
	out ddrd,temp
	ldi cursor,$01
	rcall cfg_display
	ldi caracter, '0'
	ldi boomer,80
lz:	escribir_caracter caracter
	inc caracter
	rcall mover_cursor
	dec boomer
	brne lz

rjmp main


mover_cursor:
	inc cursor
	cpi cursor, 17
	breq mover_linea2
	cpi cursor, 33
	breq limpiar
	ret

limpiar:
	;***** Apuntar a línea 1
	ldi temp,$08 ;  E=1
	out portd,temp
	ldi temp,$00 ;  E=0
	out portd,temp
	rcall delay_50us
	ldi temp,$18 ; SET & E=1
	out portd,temp
	ldi temp,$10 ; SET & E=0
	out portd,temp
	rcall delay_50us
	ldi cursor,$01
	ret


mover_linea1:
	;***** Apuntar a línea 1
	ldi temp,$88 ;  E=1
	out portd,temp
	ldi temp,$80 ;  E=0
	out portd,temp
	rcall delay_50us
	ldi temp,$08 ; SET & E=1
	out portd,temp
	ldi temp,$00 ; SET & E=0
	out portd,temp
	rcall delay_50us
	ret

mover_linea2:
	;***** Apuntar a línea 2
	ldi temp,$C8 ;  E=1
	out portd,temp
	ldi temp,$C0 ;  E=0
	out portd,temp
	rcall delay_50us
	ldi temp,$08 ; SET & E=1
	out portd,temp
	ldi temp,$00 ; SET & E=0
	out portd,temp
	rcall delay_50us
	ret

main: nop
rjmp main

cfg_display:
	rcall delay_16ms
	;****** Funcion SET Indicar cuatro bits
	ldi temp,$28 ; SET & E=1
	out portd,temp
	ldi temp,$20 ; SET & E=0
	out portd,temp
	rcall delay_50us
	;****** Funcion SET Indicar dos lineas
	ldi temp,$28 ; SET & E=1
	out portd,temp
	ldi temp,$20 ; SET & E=0
	out portd,temp
	nop
	ldi temp,$88 ; SET & E=1
	out portd,temp
	ldi temp,$80 ; SET & E=0
	out portd,temp
	rcall delay_50us
	;****** ON/OFF display
	ldi temp,$08 ; SET & E=1
	out portd,temp
	ldi temp,$00 ; SET & E=0
	out portd,temp
	nop
	ldi temp,$E8 ; SET & E=1
	out portd,temp
	ldi temp,$E0 ; SET & E=0
	out portd,temp
	rcall delay_50us
	;****** Modo de entrada (Incrementos uno en uno y mover cursor al ingresar caracter)
	ldi temp,$08 ; SET & E=1
	out portd,temp
	ldi temp,$00 ; SET & E=0
	out portd,temp
	nop
	ldi temp,$68 ; SET & E=1
	out portd,temp
	ldi temp,$60 ; SET & E=0
	out portd,temp
	rcall delay_50us
	;***** Clear display ()
	ldi temp,$08 ; SET & E=1
	out portd,temp
	ldi temp,$00 ; SET & E=0
	out portd,temp
	nop
	ldi temp,$18 ; SET & E=1
	out portd,temp
	ldi temp,$10 ; SET & E=0
	out portd,temp
	rcall delay_1ms
	rcall delay_1ms
	ret

delay_16ms:ldi temp,16
lazo3:	rcall delay_1ms
	dec temp
	brne lazo3
	ret

delay_1ms:ldi cont1,160
lazo1:	ldi cont2,100
lazo2:	nop
	dec cont2
	brne lazo2
	dec	cont1
	brne lazo1
	ret

delay_50us: ldi cont1, 16
lazo4: ldi cont2, 50
lazo5: nop
	 dec cont2
	 brne lazo5
	 dec cont1
	 brne lazo4
	 ret



 */ 
