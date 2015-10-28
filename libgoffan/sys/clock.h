#ifndef __CLOCK_H__
#define __CLOCK_H__

#define CLOCK_SECONDS				0x00
#define CLOCK_MINUTES				0x02
#define CLOCK_HOURS					0x04
#define CLOCK_WEEKDAY				0x06
#define CLOCK_DAY_OF_MONTH	0x07
#define CLOCK_MONTH					0x08
#define CLOCK_YEAR					0x09

#define CLOCK_REGA					0x0a

#define CLOCK_ATTR_PORT			0x70
#define CLOCK_GETSET_PORT		0x71

int clock_get(int attr);
void clock_set(int attr, int value);

#endif