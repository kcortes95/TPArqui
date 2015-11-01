#ifndef __TomiOS__DEFINES__
#define __TomiOS__DEFINES__




#define PIC_DATA_PORT      0x21

#define TICK_INTERVAL   55
#define DEFAULT_SCREENSAVER_TIME 10000
#define SCREENSAVER_CHANGE_TIME 5324
#define NUM_SCREENSAVERS 23

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEYBOARD_BUFFER_SIZE  32

#define NOT_PRINTABLE 0x0
#define TOTAL_KEYS  59

#define KEY_RELEASED  0x80

#define RS_PRESSED          0x36
#define RS_RELEASED         0xB6
#define LS_PRESSED          0x2A
#define LS_RELEASED         0xAA
#define CAPS_LOCK           0x3A
#define SPACEBAR            0x20

#define EMPTY 0xFF

typedef enum CURSOR_STYLE{
	CURSOR_BLOCK = 0x00,
	CURSOR_LINE = 0x0E,
	NO_CURSOR = 0x10
} CursorStyle;

typedef struct KB_STATUS {
	bool shiftEnabled;
	bool capsLockEnabled;
} kKBStatus;

typedef struct KB_BUFFER {
	word readIndex;
	word writeIndex;
	unsigned char buffer[KEYBOARD_BUFFER_SIZE];
} kKBBuffer;

typedef enum COLOR {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
} Color;

#define DEFAULT_TEXT_COLOR LIGHT_GRAY
#define DEFAULT_BG_COLOR BLACK

typedef enum SYSTEM_CALLS {
	WRITE = 0x4,
	READ = 0x3,
	CLEAR_SCREEN = 0x2,
	GET_TIME = 0xD,
	SET_TIME = 0x19,
	SET_SCREENSAVER_TIME = 0x22
} SYSCALLS;

#define RTC_PORT		0x70
#define RTC_REGISTER_PORT	0x71

typedef struct BACKUPSCREEN {
	char display[SCREEN_WIDTH*SCREEN_HEIGHT*2];
	int cursorI;
	int cursorJ;
	int backspaceLimitI;
	int backspaceLimitJ;
	CursorStyle cursorStyle;
} BackupScreen;

typedef struct U_DATE {
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char d_week;
	unsigned char d_month;
	unsigned char month;
	unsigned char year;
} DATE;

enum RTC_CONVERSION {
	RTC_SECOND = 0,
	RTC_MINUTE = 2,
	RTC_HOUR = 4,
	RTC_D_WEEK = 6,
	RTC_D_MONTH = 7,
	RTC_MONTH = 8,
	RTC_YEAR = 9,
	RTC_SETUP_B = 0xB
};

typedef struct SCREENSAVER{
	char* phrase;
	char* author;
} ScreenSaver;


#endif /* defined(__TomiOS__types__) */
