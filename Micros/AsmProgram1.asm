/*
 * AsmProgram1.asm
 *
 *  Created: 19/01/2021 04:36:33 p. m.
 * 
 
 	.include "m328Pdef.inc"
 	.def temp=r16
	.cseg
	.org 0
	rjmp reset
	.org $0028 ;Interrupción de transmisión completa
	rjmp transmite

reset:
ldi temp,$02
out ddrd,temp
sts UCSR0A,temp ;Velocidad de trans. al doble
ldi temp,(1<<TXENn)
sts UCSR0B,temp 
ldi temp, 207
sts ubrr0l,temp ; Transmitir a 9600 bps Parte baja l
ldi temp,$01
mov r15, temp
sei

main:nop
rjmp main

transmite:
sts udr0, temp ;Transmitir el dato
add temp,r15	; agregar
sts udr0,temp ;Sumar uno al recibido?
reti

USART_Init:; Set baud rate
out UBRRnH, r17 
out UBRRnL, r16 
ldi r16, (1<<RXENn)|(1<<TXENn)
out UCSRnB,r16 ; Set frame format: 8data, 2 stop bit
ldi r16,(1<<USBSn)|(3<<UCSZn0)
out UCSRnC,r16
ret
 
 

 -------------------------------------------------------------------------------------------

  .include "m328Pdef.inc"
 .equ FIN_VECTORES = $0034
 .def temp = r16
 .def modo = r17
 .def peso = r18
 .def entrada = r19
 .def opr = r20

 .cseg
 .org $0000
 rjmp RESET
 .org UTXCaddr ;$0028
 reti ;rjmp USART_TX

 RESET:
 ;Configurar UART
 ldi modo, $01
 ldi peso, $00
 rjmp main

 main:
  rcall leer_entrada
  rcall teclado
 ;rcall transmitir
 rjmp main

leer_filas:
 ;ESCRIBIR CERO PD7-PD4
 cbi portd,7
 cbi portd,6
 cbi portd,5
 cbi portd,4
 ;SALIDA PUERTO B en UNOS
 ldi temp, $FF
 out portb, temp
 ;MARCAR LECTURA EN PUERTO B
 ldi temp,$00
 out ddrb, temp
 ;MARCAR ESCRITURA PD7-PD4
 sbi ddrd,7
 sbi ddrd,6
 sbi ddrd,5
 sbi ddrd,4
 ;DELAY
 in temp, pinb ; Leer filas
 ret

leer_columnas:
 ;ESCRIBIR CEROS en PB
 ldi temp, $00
 out portb, temp
 ;SALIDA PUERTO D7-D4 en UNOS
 sbi portd,7
 sbi portd,6
 sbi portd,5
 sbi portd,4
 ;MARCAR LECTURA EN D7-D4
 cbi ddrd,7
 cbi ddrd,6
 cbi ddrd,5
 cbi ddrd,4
 ;MARCAR ESCRITURA en Puerto B
 ldi temp, $FF
 out ddrb, temp
 ;DELAY
 in temp, pind ;Leer columnas
 ret

leer_entrada:
 ldi entrada, $0F
 rcall leer_filas
 and entrada, temp ; Filtrar B3-B0
 rcall leer_columnas
 andi temp, $F0 ;Filtrar D7-D4
 or entrada, temp
 ret

teclado:
 ldi peso, $00
 ;******* DEFINICIÓN DE MACRO ******
 .macro ver_peso
	ldi opr, @1
	sbrs entrada, @0
	add peso, opr ;Fila peso C
 .endmacro
 ;******* FIN MACRO ******
 ;Pesar filas
 ver_peso 0, $0C
 ver_peso 1, $08
 ver_peso 2, $04
 ver_peso 3, $00
 ;Pesar columnas
 ver_peso 4, $03
 ver_peso 5, $02
 ver_peso 6, $01
 ver_peso 7, $00
 ;Si es presionado #
 cpi peso,$0f
 breq cambiar_teclado
 ;En caso contrario enviar simbolo
 cpi modo,$01
 breq modo_numerico
 rjmp modo_alfabetico 

;***************************************************************************
;		TECLADO
;***************************************************************************

original:
 ldi modo,$01
 ldi entrada,'#'
 ret

cambiar_teclado:
 inc modo
 cpi modo,$04
 breq original
 ldi entrada,'#'
 ret

modo_numerico:
  ldi ZL,LOW(2*numerico)
  ldi ZH,HIGH(2*numerico)
  add ZL,peso
  lpm entrada,Z
  ret

modo_alfabetico:
  ldi ZL,LOW(2*alfabetico)
  ldi ZH,HIGH(2*alfabetico)
  ldi opr,$10
  ldi temp,$02
  cpse modo,temp
  add ZL,opr
  add ZL,peso
  lpm entrada,Z
  ret

 .org $0100
 numerico: .db $30, $31, $32, $33, \
			   $34, $35, $36, $37, \
			   $38, $39, $41, $42, \
			   $43, $44, $45, $23

 alfabetico: .db 'F', 'G', 'H', 'I', \
				'J', 'K', 'L', 'M', \
				'N', 'Ñ', 'O', 'P', \
				'Q', 'R', 'S', '#', \
				'T', 'U', 'V', 'W', \
				'X', 'Y', 'Z', 'Á', \
				'É', 'Í', 'Ó', 'Ú', \
				'.', 0x20, '\n', '#'
 
 
 
 
 
 
 
   Author: MIMR
 */ 
