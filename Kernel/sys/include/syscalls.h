#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include "../../arch/include/types.h"
#include "../../arch/include/interrupts_handler.h"

int on_ack_syscall(syscall_id, ddword, ddword, ddword);

void init_syscalls();

#endif