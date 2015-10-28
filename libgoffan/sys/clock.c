#include "clock.h"
#include "internals.h"
#include "../util/util.h"

#include "video.h"


int clock_get(int attr) {
	int r;

	// outport(CLOCK_ATTR_PORT, CLOCK_REGA);

	// while ( (inport(CLOCK_GETSET_PORT) & 0x80) >> 7) {
		// putbin((inport(CLOCK_GETSET_PORT) & 0x80) >> 7);
	// }

	outport(CLOCK_ATTR_PORT, attr);
	r = inport(CLOCK_GETSET_PORT);

	return to_bcd8(r);

}

void clock_set(int attr, int value) {

	outport(CLOCK_ATTR_PORT, attr);
	outport(CLOCK_GETSET_PORT, value);

}
