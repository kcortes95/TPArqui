#include "../arch/include/types.h"
#include "include/clock.h"
#include "../arch/include/arch.h"
#include "../util/include/util.h"


uint8_t clock_get(clock_attr attr) {
	int r;

	_outport(CLOCK_ATTR_PORT, attr);
	r = _inport(CLOCK_GETSET_PORT);

	return to_bcd8(r);

}

void clock_set(clock_attr attr, uint8_t value) {

	_outport(CLOCK_ATTR_PORT, attr);
	_outport(CLOCK_GETSET_PORT, value);

}
