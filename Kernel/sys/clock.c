#include "../include/types.h"
#include "include/clock.h"
#include "include/libasm.h"
#include "../util/include/util.h"


uint8_t clock_get(clock_attr attr) {
	int r;

	out_port(CLOCK_ATTR_PORT, attr);
	r = in_port(CLOCK_GETSET_PORT);

	return to_bcd8(r);

}

void clock_set(clock_attr attr, uint8_t value) {

	out_port(CLOCK_ATTR_PORT, attr);
	out_port(CLOCK_GETSET_PORT, value);

}
