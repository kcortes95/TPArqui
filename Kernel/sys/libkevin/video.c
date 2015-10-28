#include "video.h"
#include "../util/util.h"

char *video_start_ptr = (char *) VIDEO_START_ADDR;
int current_offset = 0;

// White over black color code
char current_colour = (COLOR_BLACK << 4) | (COLOR_LIGHT_GREY & 0x0f);

void clc() {
	int i = 0;
	for (; i < BUFFER_COL*BUFFER_ROW; i+=2) {
		video_start_ptr[i+BUFFER_CHAR] = 0;
		video_start_ptr[i+BUFFER_ATTRIB] = current_colour;
	}
	set_blink(current_offset);
}

void clr(int row) {
	int i = BUFFER_COL*row*2;
	for (; i < BUFFER_COL*row*4; i+=2) {
		video_start_ptr[i+BUFFER_CHAR] = 0;
		video_start_ptr[i+BUFFER_ATTRIB] = current_colour;
	}
}

void move_up() {
	int i = BUFFER_COL*2;
	for (; i < BUFFER_COL*BUFFER_ROW; i += 2) {
		video_start_ptr[i - BUFFER_COL*2 + BUFFER_CHAR] = video_start_ptr[i + BUFFER_CHAR];
		video_start_ptr[i - BUFFER_COL*2 + BUFFER_ATTRIB] = video_start_ptr[i + BUFFER_ATTRIB];
	}
	clr(BUFFER_ROW-1);
}

void set_blink(int position) {

	// parte baja del puerto del cursor
	outport(BLINK_LOW_PORT, 0x0F);
	outport(BLINK_HIGH_PORT, (unsigned char) (position & 0xFF));

	// parte alta del puerto del cursor
	outport(BLINK_LOW_PORT, 0x0E);
	outport(BLINK_HIGH_PORT, (unsigned char) ((position & 0xFF00) >> 8));
}

void set_colour(char bg, char fg) {
	current_colour = (bg << 4) | (fg & 0x0f);
}

char get_fg_colour() {
	return current_colour & 0x0f;
}

char get_bg_colour() {
	return (current_colour & 0xf0) >> 4;
}

int get_x() {
	return current_offset % BUFFER_COL;
}

int get_y() {
	return current_offset / BUFFER_COL + 1;
}

void putcxy(char c, int x, int y) {
	video_start_ptr[y*BUFFER_COL + x + BUFFER_CHAR] = c;
	video_start_ptr[y*BUFFER_COL + x + BUFFER_ATTRIB] = current_colour;
}


void printf(const char * string, int mod, ...){
	char c;
	va_list listpointer;
	va_start(listpointer, mod);
	for(int i=0; string[i] != '\0'; i++){
		c = string[i];
		if(c == '%'){
			switch(string[i+1]){
				case 'd':	print_number(va_arg(listpointer,int));
							i++;
							break;
				case 's':	print_message(va_arg(listpointer,char *), mod);
							i++;
							break;
				default: 	_put_char(string[i], mod);
							break;
			}
		}
		else{
			_put_char(string[i], mod); // 15 para fondo negro letras blancas
		}
	}
	va_end(listpointer);
}


void putc(char c) {

	if (MIN_VISIBLE_ASCII <= c && c <= MAX_VISIBLE_ASCII) {
		video_start_ptr[current_offset + BUFFER_CHAR] = c;
		video_start_ptr[current_offset + BUFFER_ATTRIB] = current_colour;
		current_offset += 2;
	} else {
		if (c == CHAR_NEWLINE) {
			current_offset += BUFFER_COL*2 - current_offset % BUFFER_COL;
		} else if (c == CHAR_BACKSPACE) {
			video_start_ptr[current_offset - 2 + BUFFER_CHAR] = 0;
			video_start_ptr[current_offset - 2 + BUFFER_ATTRIB] = current_colour;
			current_offset -= 2;
		}
	}
	if (current_offset >= BUFFER_COL*BUFFER_ROW*2) {
		// Vemos
	}
	set_blink(current_offset/2);
}

void putnum(int i, int base) {
	char *buf, *res;

	res = itoa(i, buf, base);

	prints(res);
	
}

void putbin(int i) {
	putnum(i, 2);
}

void puti(int i) {
	putnum(i, 10);
}

void puthex(int i) {
	putnum(i, 16);
}

void prints(char *s) {
	while (*s != 0) {
		putc(*s);
		s++;
	}
}

void println(char *s) {
	prints(s);
	putc(CHAR_NEWLINE);
}
