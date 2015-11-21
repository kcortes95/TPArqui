#ifndef __UI_H__
#define __UI_H__

typedef struct {
	uint8_t x, y, w, h, fg, bg;
	char *text;
} button_t;

int contains_point(button_t *button, uint8_t x, uint8_t y);

#endif