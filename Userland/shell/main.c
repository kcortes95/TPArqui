#include <stdio.h>
#include <shell.h>
#include <stdint.h>
#include <stdlib.h>
#include <libc.h>

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	init_shell();

	register_event(MOUSE, &mouse_event);

	while (1) {
		update_shell();
	}

	return 0;
}
