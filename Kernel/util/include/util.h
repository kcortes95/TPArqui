#ifndef __UTIL_H__
#define __UTIL_H__

#include "../../arch/include/types.h"

char *itoa(int value, string str, int base);
int intlen(int n);
int strlen(string s);

uint8_t to_bcd8(uint8_t);
uint16_t to_bcd16(uint16_t);

#endif