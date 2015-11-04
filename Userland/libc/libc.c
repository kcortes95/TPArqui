#include "include/libc.h"

int write(int fd, char * str, int size) {
	return syscaller((int)WRITE, fd, str, size);
}

int read(int fd, char * str, int size) {
	return syscaller((int)READ, fd, str, size);
}
