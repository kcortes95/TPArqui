#ifndef __SOUND_H__
#define __SOUND_H__

#include "../../arch/include/types.h"
#include "../../arch/include/arch.h"

void beep(void);
void beepl(unsigned int length);
void beeplf(unsigned int length, unsigned int freq);
void nosound(void);
void sound(uint32_t frequency);
void tick_sound(void);

#endif