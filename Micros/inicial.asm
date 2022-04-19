	.include "m48def.inc"
	.def temp = r16
	.cseg
	.org 0

;***Configuraciones
	ldi temp, $00
	out ddrc, temp ;Marcar como INPUT
	out portc, temp ;Desactivar resistencia pullup en todos los pines
	com temp
	out portc, temp ;Activar resistencia pullup en todos los pines
main:
	nop
	nop
	rjmp main


	;Para dibujar una X en la matriz
	;Se realiza en cuatro movimientos simetricos
	
	

;dibuja_X:
	;El mismo numero ira tanto en filas como columnas
;	ldi r16, $81
;	ldi r16, $42
;	ldi r16, $24
;	ldi r16, $18
;	reti