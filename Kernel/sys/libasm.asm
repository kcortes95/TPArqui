global out_port
global in_port
global _cli
global _sti
global _halt

%macro PUSHALL 0
    push    RBX
    push    RDI
    push    RSI
    push    RSP
    push    R12
    push    R13
    push    R14
    push    R15
%endmacro

%macro POPALL 0
    pop     R15
    pop     R14
    pop     R13
    pop     R12
    pop     RSP
    pop     RSI
    pop     RDI
    pop     RBX
%endmacro

%macro ENTER 0
    push    rbp
    mov     rbp, rsp
    PUSHALL
%endmacro

%macro LEAVE 0
    POPALL
    mov     rsp, rbp
    pop     rbp
    ret
%endmacro

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
	ENTER
	mov rdx, [rbp+8]
	mov rax, [rbp+12]
	out dx,al
	LEAVE

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
	ENTER
	mov rdx, [rbp+8]
	mov rax, 0
	in al, dx
	LEAVE

;=========================
; _cli
;=========================
; Deshabilita
; interrupciones
_cli:
	cli
	ret

;=========================
; _sli
;=========================
; Habilita interrupciones
_sti:
	sti
	ret

;=========================
; _halt
;=========================
; Pone el CPU en Idle
; hasta que entre una
; interrupcion
_halt:
	cli
	hlt
	ret
