#ifndef __INTERNALS_H__
#define __INTERNALS_H__

extern void outport(int port, int value);
extern int inport(int port);
extern void disable_ints();
extern void enable_ints();

#endif