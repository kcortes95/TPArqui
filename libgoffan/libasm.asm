; libasm.asm

GLOBAL inport
GLOBAL outport

GLOBAL disable_ints
GLOBAL enable_ints


section .text

; int inport(int port)
; ebp+8 port
inport:
	push ebp
	mov ebp, esp

	mov edx, 0
	mov dx, [ebp+8]
	mov eax, 0

	in al, dx ; dest, port

	leave
	ret


; void outport(int port, int value)
; ebp+8 port
; ebp+12 value
outport:
	push ebp
	mov ebp, esp

	mov edx, 0
	mov eax, 0

	mov dx, [ebp+8]
	mov al, [ebp+12]
	out dx, al; dest_port, value

	leave
	ret

disable_ints:
	push ebp
	mov ebp, esp
	cli
	pop ebp
	ret

enable_ints:
	push ebp
	mov ebp, esp
	sti
	pop ebp
	ret