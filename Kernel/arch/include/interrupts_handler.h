#ifndef __ARCH_INTERRUPTS_HANDLERS__
#define __ARCH_INTERRUPTS_HANDLERS__

#include "interrupts.h"

typedef enum {
	READ = 0,
	WRITE,
	CLEAR_SCREEN,
	GET_TIME,
	SET_TIME,
	PLAY_SOUND
} syscall_id;

typedef enum {
	KEYBOARD = 0,
	TIMER_TICK,
	SYSCALL
} interrupt_id;

#define MAX_LISTENERS_ALLOWED 32

typedef struct {
	void (*call)(ddword id, ddword arg1, ddword arg2, ddword arg3);
} listener_t;

typedef struct {
	listener_t listeners[MAX_LISTENERS_ALLOWED];
	uint8_t size;
} listeners_t;

void init_interrupts();
error_t add_listener(interrupt_id id, listener_t listener);

void on_interrupt(interrupt_id id);
void on_timer_tick();
void on_keyboard();
void on_syscall();

#endif