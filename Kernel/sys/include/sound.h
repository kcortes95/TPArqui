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
int notes[7] = { 9121, 8126, 7239, 6833, 6087, 5423, 4831 };
/*
* DO - C - 9121
* RE - D - 8126
* MI - E - 7239
* FA - F - 6833
* SOL - G - 6087
* LA - A - 5423
* SI - B - 4831
*/

#endif