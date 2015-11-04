EXTERN on_keyboard
EXTERN on_syscall
EXTERN on_timer_tick

GLOBAL _load_handler
GLOBAL _get_idtr

GLOBAL _keyboard_interrupt_handler
GLOBAL _syscall_interrupt_handler
GLOBAL _tt_interrupt_handler

section .text

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
	call on_timer_tick
	mov 	al, 0x20
	out 	0x20, al
	iretq

_keyboard_interrupt_handler:
  call    on_keyboard
	mov     al, 0x20
	out     0x20, al
  iretq

_syscall_interrupt_handler:
	call 		on_syscall
	iretq
