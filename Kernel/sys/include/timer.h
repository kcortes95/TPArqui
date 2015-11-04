#ifndef __TIMER_H__
#define __TIMER_H__

#include "../../arch/include/types.h"

#define TICK_INTERVAL 55

void wait(time_t millis);

void init_timer();

#endif