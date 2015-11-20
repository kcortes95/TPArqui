#include "include/idt.h"
#include "include/ports.h"
#include "include/interrupts.h"

IDTR idtr;

void init_idt() {

	_get_idtr(&idtr);

	// Remap the irq table.
    _outport(0x20, 0x11);
    _outport(0xA0, 0x11);
    _outport(0x21, 0x20);
    _outport(0xA1, 0x28);
    _outport(0x21, 0x04);
    _outport(0xA1, 0x02);
    _outport(0x21, 0x01);
    _outport(0xA1, 0x01);
    _outport(0x21, 0x0);
    _outport(0xA1, 0x0);

    _cli();

	_outport(PIC_DATA_PORT, 0xf8); // 1111 1000
	_outport(PIC2_DATA_PORT, 0xef); // 1110 1111

    _sti();
}


void idt_set_handler(byte entry, ddword handler) {

	_cli();

	_load_handler(entry, handler, idtr.base);

	_sti();

}
