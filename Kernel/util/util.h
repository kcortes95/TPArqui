#ifndef __UTIL_H__
#define __UTIL_H__

char *itoa(int value, char *str, int base);
int intlen(int n);
int strlen(char *s);

int to_bcd8(int);
int to_bcd16(int);

#endif