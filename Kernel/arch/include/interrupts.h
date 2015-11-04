#ifndef __ARCH_INTERRUPTS__
#define __ARCH_INTERRUPTS__

#include "types.h"

extern void _cli();
extern void _sti();


extern void _load_handler(byte entry, ddword handler, ddword idt_start);

// Handlers
extern void _keyboard_interrupt_handler();
extern void _syscall_interrupt_handler();
extern void _tt_interrupt_handler();

#endif
