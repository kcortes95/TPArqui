#include "include/libc.h"

int write(int fd, char * str, int size) {
	return _syscaller((int)WRITE, fd, (uintptr_t)str, size);
}

int read(int fd, char * str, int size) {
	return _syscaller((int)READ, fd, (uintptr_t)str, size);
}

int beep() {
	return beepwo((uint32_t)1000, (uint32_t)440, (uint8_t)5);
}

int beepwo(uint32_t length, uint32_t freq, uint8_t octave) {
	return _syscaller((int)BEEP, length, freq, octave);
}

int get_time(date_t *date) {
	return _syscaller((int)GET_TIME, (uintptr_t)date, 0, 0);
}

int set_time(date_t *date) {
	return _syscaller((int)SET_TIME, (uintptr_t)date, 0, 0);
}

int shutdown(void) {
	return _syscaller((int)SHUTDOWN, 0, 0, 0);
}

