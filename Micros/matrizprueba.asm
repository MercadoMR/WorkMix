	.include "m48def.inc"
	.def temp = r16
	.cseg
	.org 0

;***Configuraciones
	ldi temp, $00
	out ddrc, temp ;Marcar como INPUT
	com temp
	out ddrb, temp ; Marcar como OUTPUT  FILAS (TIERRAS)
	out ddrd, temp ; Marcar como OUTPUT  COLUMNAS (VOLTAJES)
	ldi temp, $01
	out portc, temp ;Activar resistencia pullup en C0
	;Como fue activada la resistencia de pullup las condicionales 
	;deben funcionar de manera inversa

main:
	sbis pinc,0 ; Si el C0 esta en uno saltar la siguiente instruccion
	rcall dibuja_sigma
	rjmp main
	
dibuja_sigma:
	ldi temp, $7F 
	out portd, temp
	ldi temp, $7E  
	out portb, temp
	rcall espera
;**********************
;	LIMPIAR
	ldi temp,$00
	out portd,temp
	out portb,temp
	rcall espera
;**********************
	ldi temp, $42
	out portd, temp
	ldi temp, $BD
	out portb,temp
	rcall espera


	ldi temp,$04
	out portd, temp
	ldi temp,$DB
	out portb, temp
	rcall espera



	ldi temp,$08
	out portd, temp
	ldi temp,$E7
	out portb, temp
	rcall espera


	ldi temp,$40
	out portd,temp
	ldi temp,$DF
	out portb,temp
	rcall espera
;**********************
;	LIMPIAR
	ldi temp,$00
	out portd,temp
	out portb,temp
	rcall espera
;**********************	
	ret
		

dibuja_X:
	;El mismo numero ira tanto en filas como columnas
	;Para dibujar una X en la matriz
	;Se realiza en cuatro movimientos simetricos

	ldi temp, $81
	out portd,temp
	com temp
	out portb,temp
	rcall espera

	ldi temp, $42
	out portd,temp
	com temp
	out portb,temp
	rcall espera

	ldi temp, $24
	out portd,temp
	com temp
	out portb,temp

	rcall espera
	ldi temp, $18
	out portd,temp
	com temp
	out portb,temp
	rcall espera

	ldi temp,$00
	out portd,temp
	out portb,temp

	ret

;****Esperar a 10*10 = 100 us
espera: ldi r17, 10
lazo1: nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec r17
	brne lazo1
	ret