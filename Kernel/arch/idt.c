#include "include/idt.h"
#include "include/ports.h"
#include "include/interrupts.h"

IDTR idtr;

void init_idt() {

	_get_idtr(&idtr);

	_outport(PIC_DATA_PORT, 0xFC);
}


void idt_set_handler(byte entry, ddword handler) {

	_cli();

	_load_handler(entry, handler, idtr.base);

	_sti();

}
