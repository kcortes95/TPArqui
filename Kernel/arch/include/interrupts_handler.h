#ifndef __ARCH_INTERRUPTS_HANDLERS_H__
#define __ARCH_INTERRUPTS_HANDLERS_H__

#include "interrupts.h"

typedef enum {
	READ = 0,
	WRITE,
	OPTS,
	GET_TIME,
	SET_TIME,
	BEEP,
	PLAY_SOUND,
	EVENT,
	SHUTDOWN
} syscall_id;

typedef enum {
	KEYBOARD = 0,
	TIMER_TICK,
	SYSCALL,
	MOUSE
} interrupt_id;

#define MAX_LISTENERS_ALLOWED 32

typedef struct {
	int (*call)(syscall_id id, ddword arg1, ddword arg2, ddword arg3);
} listener_t;

typedef struct {
	listener_t listeners[MAX_LISTENERS_ALLOWED];
	uint8_t size;
} listener_pool_t;

void init_interrupts(void);
error_t add_listener(interrupt_id, listener_t);

void on_interrupt(interrupt_id, ddword, ddword, ddword, ddword);
void on_timer_tick(ddword, ddword, ddword, ddword);
void on_keyboard(ddword, ddword, ddword, ddword);
void on_syscall(ddword, ddword, ddword, ddword, ddword);
void on_mouse(ddword id, ddword arg1, ddword arg2, ddword arg3);

#endif
