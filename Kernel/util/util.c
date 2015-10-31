#include "../include/types.h"
#include "include/util.h"

char* itoa(int value, char *str, int base) {
	
	char *rc, *ptr, *low;

	if (base < 2 || base > 36) {
		*str = 0;
		return str;
	}
	rc = ptr = str;
	if (value < 0 && base == 10) {
		*ptr++ = '-';
	}
	low = ptr;
	do {
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
		value /= base;
	} while (value);
	*ptr-- = 0;

	while (low < ptr) {
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}

int intlen(int n) {
	int l = 0;
	while (n != 0) {
		n /= 10;
		l++;
	}
	return l;
}

int strlen(char *s) {
	int l = 0;
	while (*s != 0) {
		l++;
		*s++;
	}
	return l;
}

uint8_t to_bcd8(uint8_t n) {
	return ((n & 0xf0)>>4)*10 + (n & 0x0f);
}

uint16_t to_bcd16(uint16_t n) {
	return ((n & 0xf000)>>16)*1000 + ((n & 0x0f00)>>8) * 100 + to_bcd8(n & 0x00ff);
}
