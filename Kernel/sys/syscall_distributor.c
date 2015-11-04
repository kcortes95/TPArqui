#include "../arch/include/interrupts_handler.h"
#include "include/syscalls.h"
#include "include/keyboard.h"

int character = 0x0;


/**
 * Listener de syscalls
 * @param id   id del syscall
 * @param arg1 argumento 1
 * @param arg2 argumento 2
 * @param arg3 argumento 3
 */
void on_ack_syscall(syscall_id id, ddword arg1, ddword arg2, ddword arg3) {

	int i = 0;
	char c;


	if (id == READ) {

		// Pedirle al teclado que tiene para darme


		while (!is_buffer_empty()) {
			c = get_key();
			// buffer[i++] = c
		}

	} else if (id == WRITE) {

		// Hablale a video

	}

}

/**
 * Fija los listeners de las interrupciones
 */
void init_syscalls() {

	listener_t syscall_listener;

	syscall_listener.call = &on_ack_syscall;

	add_listener(SYSCALL, syscall_listener);

}

