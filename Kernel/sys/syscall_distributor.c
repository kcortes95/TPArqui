#include "../arch/include/interrupts_handler.h"
#include "include/syscalls.h"
#include "include/keyboard.h"
#include "include/video.h"
#include "include/sound.h"
#include "../util/include/util.h"
#include "include/clock.h"
#include "../arch/include/arch.h"

static int on_ack_syscall(syscall_id id, ddword arg1, ddword arg2, ddword arg3);

static int syscall_read(ddword fd, ddword buf, ddword size);
static int syscall_write(ddword fd, ddword buf, ddword size);
static int syscall_get_time(ddword time_ptr, ddword arg2, ddword arg3);
static int syscall_set_time(ddword time_ptr, ddword arg2, ddword arg3);
static int syscall_beep(ddword length, ddword freq, ddword arg3);
static int syscall_shutdown(ddword arg1, ddword arg2, ddword arg3);
static int syscall_set_opts(ddword arg1, ddword arg2, ddword arg3);
static int syscall_event(ddword id, ddword func_ptr, ddword arg3);
static int syscall_wait(ddword millis, ddword arg2, ddword arg3);

int (*syscalls[SHUTDOWN-READ+1])(ddword, ddword, ddword);
static char* song_repository_addr = (char*)0x500000;
static uint32_t song_read_offset = 0;

static int syscall_set_opts(ddword fd, ddword request, ddword params) {

	if (fd == STDOUT) {	

		if (request == REQUEST_CLEAR_SCREEN) {

			clc();

		} else if (request == REQUEST_SET_COLOR) {

			set_colour_raw(params);
		} else if (request == REQUEST_RESET) {
			set_colour(COLOR_BLACK, COLOR_LIGHT_GREY);
		}
	} else if (fd == STDFILE) {
		if ( request == REQUEST_RESET ) {

			song_read_offset = 0;
		}
	} else if (fd == STDMOUSE) {

		if (request == REQUEST_HIDE) {
			mouse_set_visible(no);
		} else if (request == REQUEST_SHOW) {
			mouse_set_visible(yes);
		} else if (request == REQUEST_SENSITIVTY) {
			mouse_set_sensitivity(params);
		}
	}


	return 0;
}

static int syscall_shutdown(ddword arg1, ddword arg2, ddword arg3) {

	_cli();
	clc();
	putsxy("Puede Apagar su Equipo", 29, 10);
	_halt();

	return 0;
}

static int syscall_get_time(ddword time_ptr, ddword arg2, ddword arg3) {
	date_t *time = (date_t*)time_ptr;
	uint8_t registerB = clock_get(REGB);

	uint8_t sec 	= clock_get_seconds();
	uint8_t min 	= clock_get_minutes();
	uint8_t hour	= clock_get_hours();
	uint8_t mon	= clock_get_month();
	uint8_t year	= clock_get_year();
	uint8_t day	= clock_get_day_of_month();

    // Convert BCD to binary values if necessary
	if (!(registerB & 0x04)) {
		sec 	= BCD2BIN(sec);
		min 	= BCD2BIN(min);
		hour 	= BCD2BIN(hour);
		day 	= BCD2BIN(day);
		mon 	= BCD2BIN(mon);
		year 	= BCD2BIN(year);
	}

	// Convert 12 hour clock to 24 hour clock if necessary
	if (!(registerB & 0x02) && (hour & 0x80)) {
		hour = ((hour & 0x7F) + 12) % 24;
	}

	time->sec 	= sec;
	time->min 	= min;
	time->hour	= hour;
	time->mon	= mon;
	time->year	= year;
	time->day	= day;

	return 0;
}

static int syscall_set_time(ddword time_ptr, ddword arg2, ddword arg3) {
	date_t *time = (date_t*)time_ptr;

	uint8_t registerB = clock_get(REGB);

	uint8_t sec 	= time->sec;
	uint8_t min 	= time->min;
	uint8_t hour	= time->hour;
	uint8_t mon 	= time->mon;
	uint8_t year	= time->year;
	uint8_t day 	= time->day;

	if (!(registerB & 0x04)) {
		sec 	= BIN2BCD(sec);
		min 	= BIN2BCD(min);
		hour 	= BIN2BCD(hour);
		day 	= BIN2BCD(day);
		mon 	= BIN2BCD(mon);
		year 	= BIN2BCD(year);

	}

	if (!(registerB & 0x02) && (hour & 0x80)) {
		hour = ((hour & 0x7F) + 12) % 24;
	}

	clock_set_seconds(sec);
	clock_set_minutes(min);
	clock_set_hours(hour);
	clock_set_month(mon);
	clock_set_year(year);
	clock_set_day_of_month(day);

	return 0;
}

static int syscall_read(ddword fd, ddword buf, ddword size) {
	int i = 0;
	char c;
	char *buffer;
	buffer = (char*)buf;

	if (fd == STDIN) {

		do {

			if (!is_buffer_empty()) {
				c = get_key();
				buffer[i++] = c;
			} 
		} while (i < size);

		return i;
	} else if (fd == STDFILE) {

		do {
			buffer[i++] = *( song_repository_addr + song_read_offset++ );
		} while ( i < size && *( song_repository_addr + song_read_offset ) != 0);
		return i;
	}

	return 0;
}

static int syscall_write(ddword fd, ddword buf, ddword size) {

	char* buffer;
	buffer = (char*)buf;

	if (fd == STDERR) {
		set_colour(COLOR_BLACK, COLOR_RED);
	}

	if (size > 1) {
		prints(buffer);
	} else {
		putc(*buffer);
	}

	if (fd == STDERR) {
		set_colour(COLOR_BLACK, COLOR_LIGHT_GREY);
	}
	return size;

}

static int syscall_beep(ddword arg1, ddword arg2, ddword arg3) {
	beep();

	return 0;
}

static int syscall_play_sound(ddword length, ddword freq, ddword arg3) {
	
	beeplf(length, freq);

	return 0;
}

static int syscall_event(ddword id, ddword func_ptr, ddword arg3) {

	listener_t listener;

	listener.call = ( int(*)(syscall_id, ddword, ddword, ddword) )func_ptr;

	if (id == MOUSE) {
		
		add_mouse_listener(listener);
	} else if (id == KEYBOARD) {

		add_listener(KEYBOARD, listener);
	}

	return 0;
}

static int syscall_wait(ddword millis, ddword arg2, ddword arg3) {

	wait(millis);
}

/**
 * Listener de syscalls
 * @param id   id del syscall
 * @param arg1 argumento 1
 * @param arg2 argumento 2
 * @param arg3 argumento 3
 */
static int on_ack_syscall(syscall_id id, ddword arg1, ddword arg2, ddword arg3) {

	return syscalls[(uint8_t)id](arg1, arg2, arg3);
}

/**
 * Fija los listeners de las interrupciones
 */
void init_syscalls() {

	listener_t syscall_listener;

	syscalls[READ] = &syscall_read;
	syscalls[WRITE] = &syscall_write;
	syscalls[OPTS] = &syscall_set_opts;
	syscalls[GET_TIME] = &syscall_get_time;
	syscalls[SET_TIME] = &syscall_set_time;
	syscalls[BEEP] = &syscall_beep;
	syscalls[PLAY_SOUND] = &syscall_play_sound;
	syscalls[EVENT] = &syscall_event;
	syscalls[WAIT] = &syscall_wait;
	syscalls[SHUTDOWN] = &syscall_shutdown;

	syscall_listener.call = &on_ack_syscall;

	add_listener(SYSCALL, syscall_listener);

}

