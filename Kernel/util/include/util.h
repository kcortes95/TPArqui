#ifndef __UTIL_H__
#define __UTIL_H__

#include "../../arch/include/types.h"

string itoa(int32_t value, char *str, uint8_t base);
string itoa2(int64_t i);
string itoa10(int64_t);
string itoa16(int64_t i);
int intlen(int64_t n);
int strlen(string s);

uint8_t to_bcd8(uint8_t);
uint16_t to_bcd16(uint16_t);

#endif