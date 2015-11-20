#include <stdio.h>
#include <shell.h>
#include <stdint.h>
#include <stdlib.h>

void sample_func(uint32_t a, uint32_t b, uint32_t c) {

	printf("%d %d %d\n", a, b, c);
}

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	init_shell();

	register_event(3, sample_func);

	while (1) {
		update_shell();
	}

	return 0;
}
