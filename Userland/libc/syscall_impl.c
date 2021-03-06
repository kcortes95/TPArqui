#include "include/libc.h"

int write(int fd, char * str, int size) {
	return _syscaller((int)WRITE, fd, (uintptr_t)str, size);
}

int read(int fd, char * str, int size) {
	return _syscaller((int)READ, fd, (uintptr_t)str, size);
}

int make_beep() {
	return _syscaller((int)BEEP, 0, 0, 0);
}

int beepwo(uint32_t length, uint32_t freq) {
	return _syscaller((int)PLAY_SOUND, length, freq, 0);
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

int set_opts(uint8_t fd, uint32_t request, uint16_t options) {
	return _syscaller((int)OPTS, fd, request, options);
}

int register_event(uint8_t id, int (*listener)(event_id, uint64_t, uint64_t, uint64_t)) {
	return _syscaller((int)EVENT, id, (uintptr_t)listener, 0);
}

int wait(uint64_t millis) {
	return _syscaller((int)WAIT, millis, 0, 0);
}
