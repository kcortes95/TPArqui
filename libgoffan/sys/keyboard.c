#include "keyboard.h"
#include "internals.h"

#include "video.h"

int getc() {

	int c = 0, t;

	do {
		c = inport(0x64) & 0x01;
		puti(c);
		println("");
	} while (c == 0);

	c = inport(0x60);

	return c;

}