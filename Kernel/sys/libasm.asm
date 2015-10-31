global out_port
global in_port

;=========================
; out_port
;=========================
; Escribe en un puerto el
; contenido de Value
;
; Argumentos
;	- Port: rbp+8
;	- Value: rbp+12
out_port:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov rdx,0
	mov rdx, [rbp+8] ; value
	mov rax, [rbp+12] ;numero del port
	out dx,al
	leave
	ret

;=========================
; in_port
;=========================
; Lee el contenido de un
; puerto
;
; Argumentos
;	- Port: rbp+8
; Salida
;	- BCD del valor leido
in_port:
	push rbp
	mov rbp, rsp
	mov rdx, [rbp+8]
	mov rax, 0
	in al, dx
	;retornamos en eax el valor del numero BCD format
	leave
	ret

