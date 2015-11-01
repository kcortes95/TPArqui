#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "defines.h"

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
#define KEYBOARD_BUFFER_SIZE 32

typedef struct {
	bool shift_enabled;
	bool caps_lock_enabled;
} keyboard_status_t;

typedef struct {
	word read_index;
	word write_index;
	unsigned char buffer[KEYBOARD_BUFFER_SIZE];
} keyboard_buffer_t;

void init_keyboard();
void on_key_received(unsigned char keycode);
void insert_key(unsigned char ascii_value);
void kKBRemoveLastKey();
unsigned char get_key();
bool is_alpha(unsigned char keycode);
bool is_buffer_empty();

#endif
