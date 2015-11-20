#include "include/interrupts_handler.h"
#include "include/idt.h"

#include "include/arch.h"
#include "../sys/include/video.h"

#include "../sys/include/timer.h"

extern void _load_handler(byte entry, ddword handler, ddword idt_start);

// Handlers
extern void _keyboard_interrupt_handler();
extern void _mouse_interrupt_handler();
extern void _syscall_interrupt_handler();
extern void _tt_interrupt_handler();

static listener_pool_t listeners_map[MOUSE - KEYBOARD];

void init_interrupts(void) {

	uint8_t i = 0;

	/**
	 *
	 *	Cargo las rutinas de atencion de interrupcion
	 * 
	 */

	idt_set_handler(0x20, (ddword)&_tt_interrupt_handler);
	idt_set_handler(0x21, (ddword)&_keyboard_interrupt_handler);
	idt_set_handler(0x80, (ddword)&_syscall_interrupt_handler);
  idt_set_handler(0x2c, (ddword)&_mouse_interrupt_handler);
  
	for (; i < MOUSE - KEYBOARD; i++) {
		listeners_map[i].size = 0;
	}

	return;
}

error_t add_listener(interrupt_id id, listener_t listener) {

	if ( listeners_map[id].size >= MAX_LISTENERS_ALLOWED ) {
		return 1;
	}

	listeners_map[id].listeners[listeners_map[id].size++] = listener;

	return 0;
}

void on_interrupt(interrupt_id id, ddword sid, ddword arg1, ddword arg2, ddword arg3) {

	uint8_t i = 0;

	for (; i < listeners_map[id].size; i++) {
		listeners_map[id].listeners[i].call((syscall_id)sid, arg1, arg2, arg3);
	}

}

void on_timer_tick(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	on_interrupt(TIMER_TICK, id, arg1, arg2, arg3);
}

void on_keyboard(ddword id, ddword arg1, ddword arg2, ddword arg3) {

	on_interrupt(KEYBOARD, id, arg1, arg2, arg3);
}

void on_syscall(ddword id, ddword rdi, ddword rsi, ddword rdx, ddword r10) {

	on_interrupt(SYSCALL, id, rdi, rsi, rdx);
}

void on_mouse(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	on_interrupt(MOUSE, id, arg1, arg2, arg3);
}
