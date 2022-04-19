
;1.-CONFIGURAR PUERTO B COMO SALIDA
; c0 y c1  salida, c2 como entrada
;2.-Configurar timer 0 en sobreflujo y preestablecido en 8 
;Habilitar interrupcipn timer
;3.-Mover las constantes de memoria de programa a
; Memoria de datos ($0100)
;unidades = 0, decenas = 0, mux = 02
;Habilitar bit de interrupcion global a 1 

;Si C2 =? 0  hacer complemento de bandera direccion(asc o desc)

;Si direc =? $01 hacer código de contador ascendente,  en otro caso hacer contador descendente

;UNIDADES=? 0A (Solo se cuentan unidades)
;Si no es igual a 0A tardar un segundo y e incrementar
;Si es igual a 0A entonces incrementar el registro de decenas
;hacer esto mismo para decenas

;REGISTRO X(L) PARA MOVER CNTES DE MEM DATOS A MEM PROG
;*** Intorrupcion 
;OVF timer 0
;apagar displays 
;mux = $06
;Mover unidades a XL
;ld temp, X
;puerto b = temp 
;puerto c = mux
;mux = $05 
;RETI 
;PARA HACER ESTOS MISMOS PASOS PARA DECNAS PERO DEJAR AL FINAL mux = $06
;YA QUE PROXIMA VEZ




;;;;;MUX OR 04 para 
;;;;;02 unidades, 01 decenas, 03 apaga
;;;;;MUX = 06 unidades, MUX = 05 DECENAS, MUX = 07 APAGAR DISPLALYS