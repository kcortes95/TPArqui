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
	OPTS,
	GET_TIME,
	SET_TIME,
	BEEP,
	PLAY_SOUND,
	SHUTDOWN
} syscall_id;

/* syscalls */

extern int _syscaller(int, int, int, int);

int get_time(date_t *);
int set_time(date_t *);
int write(int fd, char * str, int size);
int read(int fd, char * str, int size);
int beepwo(uint32_t, uint32_t);
int make_beep();
int shutdown(void);
int set_opts(uint32_t request, uint16_t options);

#define REQUEST_CLEAR_SCREEN 0
#define REQUEST_SET_COLOR 1
#define REQUEST_RESET 2

#define COLOR_BLACK					(char)0
#define COLOR_BLUE					(char)1
#define COLOR_GREEN					(char)2
#define COLOR_CYAN					(char)3
#define COLOR_RED						(char)4
#define COLOR_MAGENTA				(char)5
#define COLOR_BROWN					(char)6
#define COLOR_LIGHT_GREY		(char)7
#define COLOR_DARK_GREY			(char)8
#define COLOR_LIGHT_BLUE		(char)9
#define COLOR_LIGHT_GREEN		(char)10
#define COLOR_LIGHT_CYAN		(char)11
#define COLOR_LIGHT_RED			(char)12
#define COLOR_LIGHT_MAGENTA	(char)13
#define COLOR_LIGHT_YELLOW	(char)14
#define COLOR_WHITE					(char)15

#define build_colour(fg, bg) ( (bg << 4) | (fg & 0x0f) )

#endif