/*
 * KeypadASM.asm
 *  http://frenglish.ru/life.html
 *  Created: 19/01/2021 05:35:18 a. m.
 *   Author: MIMR
 */ 
 .include "m328Pdef.inc"
 .equ FIN_VECTORES = $0034
 .def temp = r16
 .def modo = r17
 .def peso = r18
 .def entrada = r19
 .def opr = r20
 ;.def ultimo = r21

 .cseg
 .org $0000
 rjmp RESET
 .org UTXCaddr ;$0028
 reti ;rjmp USART_TX

 RESET:
 rcall cfg_UART
 ldi modo, $01
 ldi peso, $00
 rjmp main

 main:
  rcall leer_entrada
  rcall teclado
  ;cpse entrada,ultimo
  rcall transmitir_UART
  rcall delay_ms
  rcall delay_ms
  rcall delay_ms
  rcall delay_ms
 rjmp main

cfg_UART:
 ;Poner BAUD RATE
 ldi temp,$00
 sts UBRR0H,temp
 ldi temp,207 ;12 (1MHz) 103 (8MHz) 207 (16MHz)
 sts UBRR0L,temp
 ;Velocidad doble
 ldi temp,$22
 sts UCSR0A,temp 
 ;Activar transmision
 ldi temp, (1<<TXEN0)
 sts UCSR0B, temp
 ;Formato de la trama
 ldi temp, (1 << UCSZ01) | (1 << UCSZ00)
 sts UCSR0C, temp
 ret

transmitir_UART:
lds temp, UCSR0A
sbrs temp, UDRE0
rjmp transmitir_UART
sts UDR0,entrada
;mov ultimo,entrada
ret

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
 rcall delay_ms
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
 ;delay
 rcall delay_ms
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

delay_ms: ldi temp, 255
lazo2: ldi opr, 255
lazo1: nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec opr
	brne lazo1
	dec temp
	brne lazo2
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