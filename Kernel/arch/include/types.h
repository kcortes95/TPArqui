#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define true TRUE
#define false FALSE;

#define YES true
#define NO false

#define yes YES
#define no NO

typedef unsigned char boolean;
typedef boolean bool;

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long ddword;

typedef char* string;

typedef int8_t error_t;

typedef uint64_t time_t;

#endif