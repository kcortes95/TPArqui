#ifndef __UTIL_H__
#define __UTIL_H__

char *itoa(int value, char *str, int base);
int intlen(int n);
int strlen(char *s);

uint8_t to_bcd8(uint8_t);
uint16_t to_bcd16(uint16_t);

#endif