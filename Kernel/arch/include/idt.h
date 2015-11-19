#ifndef __ARCH_IDT__
#define __ARCH_IDT__

#include "types.h"

#define PIC_DATA_PORT 0x21
#define PIC2_DATA_PORT 0xA1

#define IDT_SIZE 256

typedef struct {
	word limit;
	ddword base;
} IDTR;

extern void _get_idtr(IDTR* idtr);

void init_idt();
void idt_set_handler(byte entry, ddword handler);

#endif
