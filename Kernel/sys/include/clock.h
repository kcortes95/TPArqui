#ifndef __CLOCK_H__
#define __CLOCK_H__
/**
 *
 * Tiene la informacion del clock de la arquitectura
 * correspondiente
 * 
 */
#include "../../arch/include/clock.h"
#include "../../arch/include/types.h"

uint8_t clock_get(clock_attr attr);
void clock_set(clock_attr attr, uint8_t value);

#endif