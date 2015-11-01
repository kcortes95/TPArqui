#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "../../arch/include/video.h"
#include "../../arch/include/types.h"

void clc();
void clr(uint8_t row);
void move_up();

void set_colour(uint8_t bg, uint8_t fg);
uint8_t get_fg_colour();
uint8_t get_bg_colour();

void set_blink(uint16_t position);

void putcxy(char c, uint8_t x, uint8_t y);
void putc(char c);
void prints(string s);
void println(string s);
//void printf(const char * string, int mod, ...);

void putnum(int i, int base);
void putbin(int i);
void puti(int i);
void puthex(int i);

uint8_t get_x();
uint8_t get_y();

#endif

