	.include "m48def.inc"
	.def temp = r16
	.cseg
	.org 0
		
	ldi XL,$00
	ldi XH,$01
;*** Direccion constante con registro Z
	ldi ZL, low(display*2)
	ldi ZH, high(display*2) ;Corrimiento a la izquierda cuando mult por dos
	ldi temp, $04
lazo: lpm 
	st x+, r0
	adiw ZL,1
	dec temp 
	brne lazo ; if registro == 0
	nop
	nop 

	.cseg
display: .db $7E,$60,$5A,$47  