global out_port
global in_port

out_port:
	push ebp
	mov ebp,esp
	mov eax,0
	mov edx,0
	mov edx, [ebp+8] ; value
	mov eax, [ebp+12] ;numero del port
	out dx,al
	leave
	ret

in_port:
	push ebp
	mov ebp, esp
	mov edx, [ebp+8]
	mov eax, 0
	in al, dx
	;retornamos en eax el valor del numero BCD format
	leave
	ret

