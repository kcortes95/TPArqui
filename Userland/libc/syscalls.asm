GLOBAL _syscaller

section .text

_syscaller:
	int 80h
	ret
