#ifndef __ARCH_INTERRUPTS__
#define __ARCH_INTERRUPTS__

#include "types.h"

extern void _cli();
extern void _sti();


extern void _load_handler(byte entry, ddword handler, ddword idt_start);

// Handlers
extern void keyboardInterruptHandler();
extern void syscallInterruptHandler();
extern void TTInterruptHandler();

#endif
