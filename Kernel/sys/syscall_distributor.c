#include "../arch/include/interrupts_handler.h"
#include "include/syscalls.h"
#include "include/keyboard.h"
#include "include/video.h"

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
	char *buf;


	if (id == READ) {

		// arg1 = fd
		// arg2 = buf
		// arg3 = size

		buf = (char*)arg2;

		do {

			if (!is_buffer_empty()) {
				c = get_key();
				buf[i++] = c;
			} 
		} while (i < arg3);

	} else if (id == WRITE) {
		
		// arg1 = fd
		// arg2 = buf
		// arg3 = size
		 
		buf = (char*)arg2;

		prints(buf);
	}

	return 2;
}

/**
 * Fija los listeners de las interrupciones
 */
void init_syscalls() {

	listener_t syscall_listener;

	syscall_listener.call = &on_ack_syscall;

	add_listener(SYSCALL, syscall_listener);

}

