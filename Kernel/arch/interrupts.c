#include "include/interrupts_handler.h"

listeners_t listeners[SYSCALL - KEYBOARD];

void init_interrupts() {

	uint8_t i = 0;

	/**
	 *
	 *	Cargo las rutinas de atencion de interrupcion
	 * 
	 */

	idt_set_handler(0x20, (ddword)&_tt_interrupt_handler);
	idt_set_handler(0x21, (ddword)&_keyboard_interrupt_handler);
	idt_set_handler(0x80, (ddword)&_syscall_interrupt_handler);

	for (; i < SYSCALL - KEYBOARD; i++) {
		listeners[i].size = 0;
	}

}

error_t add_listener(interrupt_id id, listener_t listener) {

	if ( listeners[id].size >= MAX_LISTENERS_ALLOWED ) {
		return 1;
	}

	listeners[id][size++] = listener;
}

void on_interrupt(interrupt_id id, ddword id, ddword arg1, ddword arg2, ddword arg3) {

	uint8_t i = 0;

	for (; i < listeners[id].size; i++) {
		listeners[id][i].call(id, arg1, arg2, arg3);
	}

}

void on_timer_tick(ddword id, ddword arg1, ddword arg2, ddword arg3) {}
	on_interrupt(TIMER_TICK, id, arg1, arg2, arg3);
}

void on_keyboard(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	on_interrupt(KEYBOARD, id, arg1, arg2, arg3);
}

void on_syscall(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	on_interrupt(SYSCALL, id, arg1, arg2, arg3);
}

