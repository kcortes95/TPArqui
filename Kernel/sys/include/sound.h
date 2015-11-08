#ifndef __SOUND_H__
#define __SOUND_H__

#include "../../arch/include/types.h"
#include "../../arch/include/arch.h"

void play(uint32_t);
void pause();
void beep();
void beeplf(unsigned int length, unsigned int freq);

#endif