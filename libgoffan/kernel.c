
#include "sys/video.h"
#include "sys/clock.h"
#include "sys/keyboard.h"

/**********************************************
kmain() 
Punto de entrada de c�digo C.
*************************************************/
void kmain() {
	int a, b, c, d, e;


	clc();

	puti(clock_get(CLOCK_HOURS));
	putc(':');
	// puti(clock_get(CLOCK_MINUTES));
	putc(':');
	// puti(clock_get(CLOCK_SECONDS));


	return;
}
