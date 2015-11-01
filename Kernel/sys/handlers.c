#include "include/interruptsHandler.h"
#include "include/keyboard.h"

int character = 0x0;

/**
 * Listener de interrupcion de teclado
 * @param id   Lo esucho al pedo
 * @param arg1 Lo esucho al pedo
 * @param arg2 Lo esucho al pedo
 * @param arg3 Lo esucho al pedo
 */
void on_ack_keyboard(ddword id, ddword arg1, ddword arg2, ddword arg3) {

	unsigned char status = kin(KEYBOARD_STATUS_PORT);
	unsigned char keycode = kin(KEYBOARD_DATA_PORT);
	
	if (status &  0x01) {
		key_received(keycode);
	}

}

/**
 * Listener de Timer Tick
 * @param id   Lo escucho al pedo
 * @param arg1 Lo escucho al pedo
 * @param arg2 Lo escucho al pedo
 * @param arg3 Lo escucho al pedo
 */
void on_ack_timer_tick(ddword id, ddword arg1, ddword arg2, ddword arg3) {

}

/**
 * Listener de syscalls
 * @param id   id del syscall
 * @param arg1 argumento 1
 * @param arg2 argumento 2
 * @param arg3 argumento 3
 */
void on_ack_syscall(ddword id, ddword arg1, ddword arg2, ddword arg3) {

	int i = 0;
	char c;


	if (id == READ) {

		// Pedirle al teclado que tiene para darme


		while (!is_buffer_empty()) {
			c = get_key();
			buffer[i++] = c
		}

	} else if (id == WRITE) {

		// Hablale a video

	}

}

/**
 * Fija los listeners de las interrupciones
 */
void register_handlers() {

	listener_t keyboard_listener, tt_listener, syscall_listener;

	keyboard_listener.call = &on_ack_keyboard;
	tt_listener.call = &on_ack_timer_tick;
	syscall_listener = &on_ack_syscall;

	add_listener(KEYBOARD, keyboard_listener);
	add_listener(TIMER_TICK, tt_listener);
	add_listener(SYSCALL, syscall_listener);

}

