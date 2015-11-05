#ifndef __LIBC_H__
#define __LIBC_H__

#include <stdint.h>

/* common structs */
typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t mon;
	uint8_t year;
} date_t;

typedef enum {
	READ = 0,
	WRITE,
	CLEAR_SCREEN,
	GET_TIME,
	SET_TIME,
	BEEP,
	SHUTDOWN
} syscall_id;

/* syscalls */

extern int _syscaller(int, int, int, int);

int get_time(date_t *);
int set_time(date_t *);
int write(int fd, char * str, int size);
int read(int fd, char * str, int size);
int beepwo(uint32_t, uint32_t, uint8_t);
int beep();
int shutdown(void);

extern int ioctl(unsigned int fd, unsigned long request, void * params);

#define IOCTL_MOVE 0
#define IOCTL_CLR 1
#define IOCTL_SET_COLOR 2
#define IOCTL_INACTIVE 3
#define _IOCTL_HIGH_LOW(high, low)	((uint64_t)(((high) & 0xFF) << 8) | (uint64_t)((low) & 0xFF))

#define IOCTL_CURSOR(row, pos)	((void *) _IOCTL_HIGH_LOW((row), (pos)))
#define IOCTL_COLOR(fore, back)	((void *) _IOCTL_HIGH_LOW((fore), (back)))


enum IOCTL_COLOR_CODE {
	IOCTL_COLOR_BLACK = 0,
	IOCTL_COLOR_BLUE,
	IOCTL_COLOR_GREEN,
	IOCTL_COLOR_CYAN,
	IOCTL_COLOR_RED,
	IOCTL_COLOR_MAGENTA,
	IOCTL_COLOR_BROWN,
	IOCTL_COLOR_LIGHT_GRAY,

	IOCTL_COLOR_GRAY = 8,
	IOCTL_COLOR_LIGHT_BLUE,
	IOCTL_COLOR_LIGHT_GREEN,
	IOCTL_COLOR_LIGHT_CYAN,
	IOCTL_COLOR_LIGHT_RED,
	IOCTL_COLOR_LIGHT_MAGENTA,
	IOCTL_COLOR_YELLOW,
	IOCTL_COLOR_WHITE,
};

#endif