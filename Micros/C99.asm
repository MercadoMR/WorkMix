	.include "m48def.inc"
	.def temp = r16
	.def unidades = r17
	.def decenas = r18
	.def mux = r19
	.def asc = r20
	.def cont1 = r21
	.def cont2 = r22


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
	.org 0
	rjmp RESET
	.org $010
	rjmp TIM0_OVF ;;Timer 0 Overflow Handler


;***************************************************************************
;		CICLO MAIN
;***************************************************************************
main: 
	sbis pinc, 2 ; Ignorar siguiente instruccion si C2 esta en 1
	com asc
	cpi asc, $01 ; Ver direccion del contador
	breq ascendente ; Si asc igual a 1, es ascendente
	rjmp descendente ; De lo contrario descendente
	rjmp main

ascendente:
	inc unidades
	cpi unidades,$0A ; Si llego a 10 
	breq aumentar_decenas
	rjmp retraso

descendente:
	dec unidades
	cpi unidades,$FF ; Si estaba en cero y resto 1
	breq disminuir_decenas
	rjmp retraso


retraso: rcall delay_500ms
	rcall delay_500ms
	rjmp main


;***************************************************************************
;		SUBRUTINAS
;***************************************************************************

aumentar_decenas:
	ldi unidades,$00 ;Poner en cero las unidades
	inc decenas
	cpi decenas, $0A ;Si llego a 10
	breq ceros ; Poner decenas a ceros
	rjmp retraso

disminuir_decenas:
	ldi unidades,$09 ;Poner en nueve las unidades
	dec decenas
	cpi decenas, $FF ;Si estaba en cero y reste uno
	breq nueves ;Poner decenas en 9 
	rjmp retraso

ceros: 
	ldi decenas,$00
	rjmp retraso

nueves:
	ldi decenas,$09
	rjmp retraso

delay_500ms: ldi cont2, 250
lazo2: ldi cont1, 200
lazo1: nop
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
	ret

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

;***************************************************************************
;		INTERRUPCIONES
;***************************************************************************

RESET:
	rcall iniciar_const ;Cargar constantes en memoria datos
	ldi temp,$02
	out tccr0b,temp ; Preescalador a 64 
	ldi temp,$01
	;out tccr0b,temp ; Preescalador a 8 
	sts timsk0,temp ; Activar interrupcion de sobreflujo
	sei ;Activar interrupciones

	;	Configurar B0 a B7 como salida
	ldi temp, $FF
	out ddrb, temp
	;	Configurar C0 y C1 como salida, y C2 como entrada
	ldi temp, $03
	out ddrc, temp
	;	Resistencia pull-up en C2 y 1s en C0,C1
	ldi temp, $07
	out portc,temp

	ldi asc,$01 ;	Si esta en 1 el contador es ascendente
	ldi unidades,$00
	ldi decenas, $00
	ldi mux,$06 ; Iniciar con unidades
	rjmp main

TIM0_OVF: ldi temp,$07
	out portc, temp ; Apagar displays
	cpi mux, $06 ; Si voy a dibujar unidades
	breq dibujar_unidades
	cpi mux, $05 ; Si voy a dibujar decenas
	breq dibujar_decenas
	reti
	
dibujar_unidades:
	mov XL, unidades ;Copiar direccion donde esta constante, e.g, XL = $07 -> X = $0107
	ld temp, X ; Cargar constante del numero a dibujar en temp
	out portb, temp ; Mostrar numero
	out portc, mux  ; Activar display unidades
	ldi mux, $05 ; Dejar para proxima vez decenas
	reti

dibujar_decenas:
	mov XL, decenas ;Copiar direccion donde esta num. a dibujar, e.g, XL = $09 -> X = $0109
	ld temp, X ; Cargar constante del numero a dibujar en temp
	out portb, temp ; Sacar numero
	out portc, mux  ; Activar display unidades
	ldi mux, $06 ; Dejar para proxima vez unidades
	reti
	
	.dseg 
	.org $0100	  ; Posicion 0x0100 de nuestra memoria de datos (Inicio de SRAM)
display: .byte 10 ;	Reservar espacio para 10 bytes (constante de cada numero a dibujar),
				  ; que luego serán inicializados en tiempo de ejecucion.