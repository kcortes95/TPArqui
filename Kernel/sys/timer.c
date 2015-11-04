#include "../arch/include/interrupts_handler.h"
#include "include/timer.h"

time_t millis_ellapsed = 0;

void on_tick(syscall_id id, ddword arg1, ddword arg2, ddword arg3) {
	// Ignoro los parametros
	

	millis_ellapsed += TICK_INTERVAL;
}

void wait(time_t millis) {

	time_t eta = millis_ellapsed + millis;

	while ( eta > millis_ellapsed);
}

void init_timer() {

	listener_t tt_listener;

	tt_listener.call = &on_tick;

	add_listener(TIMER_TICK, tt_listener);
}

