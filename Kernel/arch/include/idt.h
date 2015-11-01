#ifndef __ARCH_IDT__
#define __ARCH_IDT__

#include "types.h"

#define IDT_SIZE 256

typedef struct {
	word limit;
	ddword base;
} IDTR;

extern void _get_idtr(IDTR* idtr);
void init_idt();

#endif
