#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include "../../arch/include/types.h"
#include "../../arch/include/interrupts_handler.h"

#define STDIN		0
#define STDOUT 	1
#define STDERR 	2
#define STDFILE	3
#define STDMOUSE 4

#define REQUEST_CLEAR_SCREEN 0
#define REQUEST_SET_COLOR 1
#define REQUEST_RESET 2
#define REQUEST_HIDE 3
#define REQUEST_SHOW 4
#define REQUEST_SENSITIVTY 5

void init_syscalls();

#endif