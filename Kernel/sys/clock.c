#include "../arch/include/types.h"
#include "include/clock.h"
#include "../arch/include/arch.h"
#include "../util/include/util.h"

int isleapyear(uint8_t year){
	return ((!(year%4) && (year%100)) || !(year%400));
}

int valid_time(uint8_t sec, uint8_t min, uint8_t hrs) {

	if( sec >60 || sec < 0	||
		min >60 || min < 0	||
		hrs >24 || sec < 0)
	{
		return 0;
	}
	return 1;

}
//1 valid, 0 invalid
int valid_date(uint8_t year, uint8_t month, uint8_t day){
	uint8_t monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 0 || month < 1 || year < 0 || month > 12) {
		return 0;
	}
	if (isleapyear(year) && month == 2) {
		monthlen[1]++;
	}
	if (day>monthlen[month-1] || day < 1) {
		return 0;
	}
	return 1;
}

/*===================================
*************    GETTERS
===================================*/

uint8_t clock_get(clock_attr attr) {
	_outport(CLOCK_ATTR_PORT, attr);
	return _inport(CLOCK_GETSET_PORT);
}

uint8_t clock_get_seconds() {
	return clock_get(SECONDS);
}

uint8_t clock_get_minutes() {
	return clock_get(MINUTES);
}

uint8_t clock_get_hours() {
	return clock_get(HOURS);
}

uint8_t clock_get_weekday() {
	return clock_get(WEEKDAY);
}

uint8_t clock_get_day_of_month() {
	return clock_get(DAY_OF_MONTH);
}

uint8_t clock_get_month() {
	return clock_get(MONTH);
}

uint8_t clock_get_year() {
	return clock_get(YEAR);
}

/*===================================
*************    SETTERS
===================================*/

void clock_set(clock_attr attr, uint8_t value) {

	_outport(CLOCK_ATTR_PORT, attr);
	_outport(CLOCK_GETSET_PORT, value);

}

void clock_set_seconds(uint8_t value) {
	clock_set(SECONDS, value);
}

void clock_set_minutes(uint8_t value) {
	clock_set(MINUTES, value);
}

void clock_set_hours(uint8_t value) {
	clock_set(HOURS, value);
}

void clock_set_weekday(uint8_t value) {
	clock_set(WEEKDAY, value);
}

void clock_set_day_of_month(uint8_t value) {
	clock_set(DAY_OF_MONTH, value);
}

void clock_set_month(uint8_t value) {
	clock_set(MONTH, value);
}

void clock_set_year(uint8_t value) {
	clock_set(YEAR, value);
}
