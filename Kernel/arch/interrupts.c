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

error_t add_listener(syscall_id id, listener_t listener) {

	if ( listeners[id].size >= MAX_LISTENERS_ALLOWED ) {
		return 1;
	}

	listeners[id][size++] = listener;
}

void on_interrupt(interrupt_id id) {

	uint8_t i = 0;

	for (; i < listeners[id].size; i++) {
		listeners[id][i].call();
	}

}

void on_timer_tick() {

	on_interrupt(TIMER_TICK);
}

void on_keyboard() {
	on_interrupt(KEYBOARD);
}

void on_syscall() {
	on_interrupt(SYSCALL);
}

