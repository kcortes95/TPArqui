#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <shell.h>
#include <stdint.h>

#define INVALID_DATE "Invalid date inserted, please respect dd/mm/yy format & insert a valid date.\n"
#define INVALID_TIME "No arguments were sent to command settime format musut be ss:mm:hh \n"
#define INVALID_SCREEN_SAVER_TIME "Invalid time delay was introduced for screen saver, please use following format:\n \"ss:mm:hh\". Note timer cannot exceed 24hs nor be shorter than 5 seconds\n"

typedef enum {
	kReadingInitial,
	kReadingDuration,
	kReadingPitch,
	kReadingOctave
} NoteParserState;

typedef enum {
	NOTE_C = 0,
	NOTE_C_SHARP,
	NOTE_D,
	NOTE_D_SHARP,
	NOTE_E,
	NOTE_F,
	NOTE_F_SHARP,
	NOTE_G,
	NOTE_G_SHARP,
	NOTE_A,
	NOTE_A_SHARP,
	NOTE_B,
	NOTE_P
} note_id;

typedef struct {
	uint8_t duration;
	uint8_t pitch;
	uint8_t octave;
} note_t;

typedef struct {
	char title[30];
	uint8_t default_duration;
	uint8_t default_octave;
	uint16_t beat;
	note_t notes[100];
	uint8_t read_notes;
} song_t;

void echo(char**, int);
void clear(char**, int);
void date(char**, int);
void time(char**, int);
void set_date(char**, int);
void settime(char**, int);
int parse_date(char*, int*, int*, int*);
int parse_time(char*, int*, int*, int*);
int is_num(char);
int valid_time(int, int, int);
int valid_date(int, int, int);
int is_leap_year(int);
void getchar_cmd(char**, int);
void printf_cmd(char**, int);
void scanf_cmd(char**, int);
void reset_vect(char vec[]);
void help_error_print();
void help(char**, int); 
void halt_system(char** args, int argc);
void beep(char** args, int argc);
void mouse_hide(char *argv[], int argc);
void mouse_show(char *argv[], int argc);
void mouse_sensitivity(char *argv[], int argc);
void mouse_test(char *argv[], int argc);
void credits(char *argv[], int argc);
void play_sound(char *argv[], int argc);
void commands(char** args, int argc);
void print_ascii_table(char** args, int argc);
void setcolor(char** args, int argc);
void screen_saver_delay(char** args, int argc);

void unhang_click();
void hang_for_click();

#endif