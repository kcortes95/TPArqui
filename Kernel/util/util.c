#include "../arch/include/types.h"
#include "include/util.h"

string itoa(int32_t value, char *str, uint8_t base) {
	
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

int intlen(int64_t n) {
	int l = 0;
	while (n != 0) {
		n /= 10;
		l++;
	}
	return l;
}

int strlen(char* s) {
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


#define INT_DIGITS 19		/* enough for 64 bit integer */

char *itoa10(int64_t i) {
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			/* i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}

char *itoa16(int64_t i) {
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */
  uint8_t rem;
  do {
  	rem = i % 16;
  	if (rem >= 10)
  		*--p = 'A' + rem - 10;
  	else
  		*--p = '0' + rem;
    i /= 16;
  } while (i != 0);
  return p;
}

char *itoa2(int64_t i) {
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[64 + 2];
  char *p = buf + 64 + 1;	/* points to terminating '\0' */
  do {
  	*--p = '0' + (i % 2);
    i /= 2;
  } while (i != 0);
  return p;
}

