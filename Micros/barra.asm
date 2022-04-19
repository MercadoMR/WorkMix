	.include "m48def.inc" ;Para poder leer este archivo
	.def temp = r16  ;Acceder a un registro mediante simbolo
	.def cont1 = r17
	.def cont2 = r18
	.def sal = r19
	.set abit = 0
	.cseg ; Empieza un segmento de código
	.org 0 ;Esto es en la memoria de programa

	ldi temp,$00 ; Cargar a 8 ceros
	;; Configuracion de control C0 (ascendente) y C1 (descendente)
	out	ddrc,temp ; Habilitar lectura C0 y C1 como lectura (INPUT)
	ldi temp,$03 ; Poner 3 (11) en temp 
	out portc, temp ; Habilitar las resistencias de pull-up en C0 y C1 
	ldi temp,$ff ; Cargar el registro a unos
	out ddrb, temp ; Habilitar B0...B7 como salida (OUTPUT)
	ldi sal,$00 ; Poner en ceros el registro al principio

main:
	;**LECTURA DE DIRECCION
	in temp,pinc ; Pongo en temporal lo que leo del puerto C
	andi temp,$03 ;Filtro para solo obtener lo de C0 y C1
	;**MOVER A ASCENDENTE
	cpi temp, $02 ; Resta con $01, Se presiono C0
	breq barra_asc ; Si la bandera Z = 1 entonces saltar a la direccion
	;**MOVER DESCENDENTE
	cpi temp, $01 ; Resta con $02, Se presiono C1
	breq barra_desc ;
    ;**LIMPIAR SALIDA SI NO ENTRA
    ldi sal,$00 ; Si no esta entrando significa que no esta presionado asi que regresar a 0 registro
    out portb,sal ;Poner a ceros la salida
	rjmp main


barra_asc:
	lsl sal  ; recorrer a la izquierda lo que hay
	ori sal,$01 ; sumar 1 en LSB
	rcall delay_125ms ;esperar 125ms
	out portb,sal ; Mostrar un bit mas
	rjmp main ;regresar


barra_desc: 
	lsr sal ;Recorrer a la derecha lo que hay 
	ori sal,$80 ; Sumar 1 en el MSB
	;***Esperar poco más de un segundo para mas visibilidad
    rcall delay_125ms ;esperar 125ms
	out portb,sal ; Mostrar un bit mas
	rjmp main ;regresar

;;*********** subrutinas
;Son dos ciclos el externo de 50 y el interno de 250 haciendo... ¿8 instrucciones? que toman 10 us
;De esta forma esta subrutina toma aprox 50*250*10 = 125 000 us = 125 ms
;Se puede modificar los valores cargados en los contadores para hacer mas largo o corto
delay_125ms: ldi cont2, 50
lazo2:	ldi cont1, 250 
lazo1:	nop
	nop
	nop
	nop
	nop
	nop
	nop; siete cilcos reloj nops
	dec cont1 ; ciclo reloj 
	brne lazo1 ; dos ciclos
	dec cont2
	brne lazo2 ;
	ret

;255*255*8 = 520 200 us 
delay_520ms: ldi cont2, 255
cir2:	ldi cont1, 255
cir1:	nop
	nop
	nop
	nop
	nop; siete cilcos reloj nops
	dec cont1 ; ciclo reloj 
	brne cir1 ; dos ciclos
	dec cont2
	brne cir2 ;
	ret