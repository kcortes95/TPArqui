EXTERN on_keyboard
EXTERN on_mouse
EXTERN on_syscall
EXTERN on_timer_tick

EXTERN mouse_handler

EXTERN puti
EXTERN putc

GLOBAL _load_handler
GLOBAL _get_idtr

GLOBAL _keyboard_interrupt_handler
GLOBAL _mouse_interrupt_handler
GLOBAL _syscall_interrupt_handler
GLOBAL _tt_interrupt_handler

GLOBAL _force_int33
GLOBAL _mouse_init

section .text

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
; _get_idtr
;=========================
; void _get_idtr(void*)
;=========================
; Carga el contenido del
; registro IDTR en rdi
;
; Argumentos
;	- Puntero: rdi
_get_idtr:
	sidt [rdi]
	ret

_load_handler:

	mov rax, rsi

	shl rdi, 4			; quickly multiply rdi by 16 to go to the corresponding place in the table
	add rdi, rdx		; adds the base address of the idt table to the place in the table
	stosw						; store the low word (15..0)
	shr rax, 16
	add rdi, 4			; skip the gate marker
	stosw						; store the high word (31..16)
	shr rax, 16
	stosd						; store the high dword (63..32)

	ret

; Handlers

_tt_interrupt_handler:
	call		on_timer_tick
	mov 		al, 0x20
	out			0x20, al
	iretq

_keyboard_interrupt_handler:
  call    on_keyboard
	mov     al, 0x20
	out     0x20, al
  iretq

_syscall_interrupt_handler:
	call 		on_syscall
	iretq

_mouse_interrupt_handler:
	call		mouse_handler
	iretq


_force_int33:
	mov rax, -1
	; mov rdi, -1
	mov rsi, -1
	mov rdx, -1
	mov r8, -1
	mov ax, di
	int 33h
	ret

_mouse_init:
	ENTER

	mov rdi, 0
	mov di, 4
	call puti

	mov di, ' '
	call putc
	mov rax, 0
	mov ax, 0

	mov di, ax
	call puti

	mov di, ' ',
	call putc

	int 33h
	
	mov di, ax
	call puti

	mov di, ' '
	call putc

	mov di, bx
	call puti

	mov di, ' '
	call putc

	mov ax, 1
	int 33h



	LEAVE



