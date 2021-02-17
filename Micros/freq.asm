;;;https://www.avrfreaks.net/forum/max-voltage-digital-io-pin
	.include "m48def.inc"
	.def temp = r16
	.def con_uni = r17 ;; Estos contadores son para
	.def con_dec = r18 ;; contar cada flanco que haya 
	.def con_cen = r19 ;; en la entrada, esto para saber la frecuencia de la señal

	.def aux_uni = r20 ;; Los auxiliares serviran para guardar
	.def aux_dec = r21 ;; los datos de los flancos contados de manera temporal  
	.def aux_cen = r22 ;; para que cuando se dibujen en los displays no cambien
	.def mux = r23

	;***Definicion de constantes para dibujar numeros
	; .set nueve = $77
	; .set ocho = $FF
	; .set siete = $23
	; .set seis = $7E
	; .set cinco = $76 
	; .set cuatro = $53
	; .set tres = $67
	; .set dos = $6D
	; .set uno = $03
	; .set cero = $3F

	.cseg
	.org $000
	rjmp RESET
	.org $001
	rjmp INT_0 ; Interrupcion externa para contar ciclos de la senial de entrada
	.org $00B ; Usar el timer 1 que es de 16 bits
	rjmp   TIM1_COMPA  ; Timer1 Compare A Handler (Interrupcion comparacion OCR1A)
	.org $010
	rjmp TIM0_OVF ;;Timer 0 Overflow Handler


;***************************************************************************
;		CICLO MAIN
;***************************************************************************
main: nop
	rjmp main


;***************************************************************************
;		SUBRUTINAS
;***************************************************************************

iniciar_const:

	ldi XL, LOW(display)  ; Guardar parte baja de la direccion apuntada ($0100) -> XL = $00
	ldi XH, HIGH(display) ; Guardar parte alta de la direccion apuntada ($0100) -> XH = $01

	ldi temp, $3F
	st X+, temp ;	Cargar cero
	ldi temp, $03
	st X+, temp ;	Cargar uno
	ldi temp, $6D
	st X+, temp ;	Cargar dos
	ldi temp, $67
	st X+, temp ;	Cargar tres
	ldi temp, $53
	st X+, temp ;	Cargar cuatro
	ldi temp, $76
	st X+, temp ;	Cargar cinco
	ldi temp, $7E
	st X+, temp ;	Cargar seis
	ldi temp, $23
	st X+, temp ;	Cargar siete
	ldi temp, $FF
	st X+, temp ;	Cargar ocho
	ldi temp, $77
	st X, temp ;	Cargar nueve
	ldi XL, LOW(display) ; Indicar de nuevo parte baja
	ldi XH, HIGH(display) ; Indicar de nuevo parte alta
	ret

;	Configuración del timer de 16 bits para saber la freq.
cfg_timer16: 
	ldi temp, $0B ; Valores para CTC y Preescalador a 64
	sts tccr1b, temp ; tccr1a tiene 0 en este caso por eso no lo cargo 
	ldi temp, $02 ; Valores para activar interrupcion comparacion con OCR1A
	sts timsk1, temp ; Registro extendido
	ldi temp, $3D ; Cargar nuestro numero a comparar 15625 ($3D09)
	sts OCR1AH, temp ;Cargar primero parte alta
	ldi temp, $09 ; Cargar parte baja de nuestro numero a comparar 15625 ($3D09)
	sts OCR1AL, temp ;Cargar uego parte baja
	ret

;	Configuracion del timer de 8 bits para dibujar los números
cfg_timer8:
    ldi temp,$01
	out tccr0b,temp ; Preescalador a 8 
	sts timsk0,temp ; Activar interrupcion de sobreflujo
	ret    

;	Configuracion de la interrupcion de flancos
cfg_int0:
    ldi temp,$03 ;Flanco de subida genera la interrupcion
	sts eicra,temp ;Aplicar lo anterior para el pin de INT0
    ldi temp,$01 
	out eimsk,temp ;Activar INT0
    ret

;***************************************************************************
;		INTERRUPCIONES
;***************************************************************************

RESET:
	rcall iniciar_const ;Cargar constantes en memoria datos
	; Cargar primero la parte alta y luego la baja del registro de comparacion (Se lee al reves)
	; Para comparacion cada 1s cargar 15625 ($3D09) en OCR1A
	rcall cfg_timer16
	rcall cfg_timer8
	rcall cfg_int0
	sei ;Activar bit de interrupciones
	;	Configurar B0 a B7 como salida
	ldi temp, $FF
	out ddrb, temp
	;	Configurar C0, C1 y C3 como salida
	ldi temp, $07
	out ddrc, temp
	;	Configuracion de D2 como entrada se hace automaticamente
	ldi mux, $06 ; Iniciar dibujando unidades
	;	Iniciar contadores en 0
	ldi con_uni,$00
	ldi con_dec,$00
	ldi con_cen,$00
	ldi aux_uni,$00
	ldi aux_dec,$00
	ldi aux_cen,$00
	rjmp main

INT_0:
    inc con_uni
    cpi con_uni,$0A
	breq aumentar_decenas
    reti

aumentar_decenas:
    ldi con_uni,$00 ;Poner unidades a cero de nuevo
	inc con_dec
	cpi con_dec,$0A ; Si decenas es 10
	breq aumentar_centenas
	reti

aumentar_centenas:
	ldi con_dec,$00 ;Poner decenas a cero
	inc con_cen
	cpi con_cen,$0A ;Poner a cero
	breq ceros
	reti

ceros: ldi con_cen,$00
	reti

TIM1_COMPA:
	;	Copiar último conteo
	mov aux_uni, con_uni
	mov aux_dec, con_dec
	mov aux_cen, con_cen 
    ;	Poner a cero los contadores para el siguiente segundo
	ldi con_uni, $00
	ldi con_dec, $00
	ldi con_cen, $00
    reti

TIM0_OVF: ldi temp,$07
	out portc, temp ; Apagar displays
	cpi mux, $06 ; Si voy a dibujar unidades
	breq dibujar_unidades
	cpi mux, $05 ; Si voy a dibujar decenas
	breq dibujar_decenas
	cpi mux, $03 ; Si voy a dibujar centenas
	breq dibujar_centenas
	reti
	
dibujar_unidades:
	mov XL, aux_uni ;Copiar direccion donde esta constante, e.g, XL = $07 -> X = $0107
	ld temp, X ; Cargar constante del numero a dibujar en temp
	out portb, temp ; Mostrar numero
	out portc, mux  ; Activar display unidades
	ldi mux, $05 ; Dejar para proxima vez decenas
	reti

dibujar_decenas:
	mov XL, aux_dec ;Copiar direccion donde esta num. a dibujar, e.g, XL = $09 -> X = $0109
	ld temp, X ; Cargar constante del numero a dibujar en temp
	out portb, temp ; Sacar numero
	out portc, mux  ; Activar display unidades
	ldi mux, $03 ; Dejar para proxima vez centenas
	reti

dibujar_centenas:
	mov XL, aux_cen ;Copiar direccion donde esta num. a dibujar, e.g, XL = $09 -> X = $0109
	ld temp, X ; Cargar constante del numero a dibujar en temp
	out portb, temp ; Sacar numero
	out portc, mux  ; Activar display unidades
	ldi mux, $06 ; Dejar para proxima vez unidades
	reti

	.dseg 
	.org $0100	  ; Posicion 0x0100 de nuestra memoria de datos (Inicio de SRAM)
display: .byte 10 ;	Reservar espacio para 10 bytes (constante de cada numero a dibujar),
				  ; que luego serán inicializados en tiempo de ejecucion.