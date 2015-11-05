#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include "../../arch/include/types.h"
#include "../../arch/include/interrupts_handler.h"

#define STDOUT 	1
#define STDERR 	2

void init_syscalls();

#endif