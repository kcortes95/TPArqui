#include <command.h>
#include <string.h>
#include <shell.h>
#include <stdio.h>
#include <libc.h>

static int parse_sounds(char* raw, song_t* parsed_songs);
static void parse_sound(char *raw, song_t* parse_song);
static void parse_title(char *raw, song_t* parse_song);
static void parse_header(char *raw, song_t* parse_song);
static void parse_body(char *raw, song_t* parse_song);

static int padding(char *s);

char waiting_click = 0;

/*****Commands functions*****/


void help(char *argv[], int argc) {
	int cmd_index;
	cmd_entry* table = get_command_table();
	if (argc == 1) {
		cmd_index = get_cmd_index(argv[0]);
		if (cmd_index != -1) {
			printf("%s", table[cmd_index].help);
		} else {
			help_error_print(table);
		}
	} else if (argc == 0) {
		help_error_print(table);
	}
}

void echo(char** args, int argc) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s ", args[i]);
	}
	putc('\n');
}

void clear(char** args, int argc) {
	set_opts(STDOUT, REQUEST_CLEAR_SCREEN, 0);
}

void commands(char** args, int argc) {
	printf("Available commands are: \n");
	print_commands();
}


void date(char** args, int argc) {
	date_t time_struct;
	get_time(&time_struct);
	
	printf("%d/%d/%d\n",
		time_struct.day,
		time_struct.mon,
		time_struct.year
	);
}

void time(char** args, int argc) {
	date_t time_struct;
	get_time(&time_struct);

	printf("%d:%d:%d\n",
		time_struct.hour,
		time_struct.min,
		time_struct.sec
	);
}

void set_date(char** args, int argc) {
	date_t time_struct;
	int days, months, years;

	get_time(&time_struct);
	if (argc <1){
		fprintf(STDERR, INVALID_DATE);
		return;
	}
	if (!parse_date(args[0], &days, &months, &years)){
		fprintf(STDERR, INVALID_DATE);
		return;
	}
	time_struct.year = years;
	time_struct.mon = months;
	time_struct.day = days;

	set_time(&time_struct);
}

void settime(char** args, int argc) {
	date_t time_struct;
	int seconds, minutes, hours;

	get_time(&time_struct);
	if (argc < 1) {
		fprintf(STDERR, INVALID_TIME);
		return;
	}	
	if (!parse_time(args[0], &seconds, &minutes, &hours)) {
		fprintf(STDERR, INVALID_TIME);
		return;
	}


	time_struct.sec = seconds;
	time_struct.min = minutes;
	time_struct.hour = hours;

	set_time(&time_struct);

}

void halt_system(char** args, int argc) {
	shutdown();
}

void print_ascii_table(char** args, int argc) {
	int i;

	for (i = 0; i < 128; i++) {
		printf("%x: %c", i, i < 32 ? ' ' : i);

		if (i % 8) {
			printf(" \t| ");
		} else {
			putc('\n');
		}
	}

	putc('\n');
}


void setcolor(char** args, int argc) {
	int fore, back;
	if (argc != 2) {
		printf("usage: setcolor foreground background\n");
		printf("\nColors are:\n");

		printf("\tdarker       | lighter\n");
		printf("\tblack:     0 | light gray:   8\n");
		printf("\tblue:      1 | celurean:     9\n");
		printf("\tgreen:     2 | light green: 10\n");
		printf("\tcyan:      3 | light cyan:  11\n");
		printf("\tred:       4 | light red:   12\n");
		printf("\tmagenta 1: 5 | magenta 2:   13\n");
		printf("\tbrown:     6 | yellow:      14\n");
		printf("\tgray 1:    7 | white:       15\n");
		printf("\nnote: you might not choose two of the same.\n");
		return;
	}

	fore = atoi(args[0]);
	back = atoi(args[1]);

	if (fore == back) {
		fprintf(STDERR, "Aaaand you chose two of the same...\n Nope.\n");
		return;
	}

	if (fore >= 16 || back >= 16 || fore < 0 || back < 0) {
		fprintf(STDERR, "Invalid parameter: %d, %d\n", fore, back);
		return;
	}

	set_opts(STDOUT, REQUEST_SET_COLOR, build_colour(fore, back));
	clear(args, argc);
}

void beep(char *argv[], int argc) {
	make_beep();
}

void mouse_hide(char* argv[], int argc) {
	set_opts(STDMOUSE, REQUEST_HIDE, 0);
}

void mouse_show(char* argv[], int argc) {
	set_opts(STDMOUSE, REQUEST_SHOW, 0);
}

void mouse_sensitivity(char* argv[], int argc) {
	uint16_t sensitivty;
	if (argc != 1) {
		printf("usage: mouse_sensitivity [sensitivty]\n");
		printf("0 < sensitivty <= 100\n");
		return;
	}
	sensitivty = atoi(argv[0]);
	if (sensitivty < 0 || sensitivty > 100) {
		printf("usage: mouse_sensitivity [sensitivty]\n");
		printf("0 < sensitivty <= 100\n");
		return;
	}
	set_opts(STDMOUSE, REQUEST_SENSITIVTY, 101-sensitivty);
}

void hang_for_click() {
	waiting_click = 1;
	set_listening_mouse(0);
}

void unhang_click() {
	waiting_click = 0;
	set_listening_mouse(1);
}

void mouse_test(char *argv[], int argc) {

	set_opts(STDOUT, REQUEST_SET_COLOR, build_colour(COLOR_BLACK, COLOR_LIGHT_GREY));

	clear(argv, argc);

	hang_for_click();

	while (1) {
		if (!waiting_click) {
			set_opts(STDOUT, REQUEST_RESET, 0);
			clear(argv, argc);
			break;
		}
	}
}

char *credit_text[] = {
	"Creditos",
	"",
	"Integrantes",
	"Martin Goffan",
	"Eric Horvat",
	"Kevin Cortes",
	"",
	"Profesores",
	"Santiago Valles",
	"Augusto Nizzo Mc Intosh",
	"Rodrigo Rearden",
	""
};

// https://en.wikipedia.org/wiki/Scientific_pitch_notation
// 
static float base_frequencies[] = {
	16.352, // C   0
	17.324, // C#  1
	18.354, // D   2
	19.445, // D#  3
	20.602, // E   4
	21.827, // F   5
	23.125, // F#  6
	24.500, // G   7
	25.957, // G#  8
	27.500, // A   9
	29.135, // A#  10
	30.868, // B   11
	0,			// Pause  12
};

static int padding(char *s) {
	return (80-strlen(s))/2;
}

void credits(char *argv[], int argc) {
	
	char songs[4096];
	song_t parsed_songs[20];
	int choice = -1;
	int i = 0, j = 0;
	note_t current_note;
	uint32_t one_note_length;
	char **s = credit_text;

	clear(argv, argc);

	for (j = 0; j <= 25; j++){
		printf("\n");
	}

	fgets(STDFILE, songs, 4096);

	parse_sounds(songs, parsed_songs);

	// StarWars es la 6
	choice = 6;

	one_note_length = 60000 / parsed_songs[choice-1].beat * 4;

	for (; i < parsed_songs[choice-1].read_notes; i++) {

		current_note = parsed_songs[choice-1].notes[i];
		for (j = 0; j < padding(*s); j++) {
			putc(' ');
		}
		printf("%s\n", *s);
		s++;

		if (i % 11 == 0) {
			s = credit_text;
		}

		beepwo( one_note_length / current_note.duration,
			base_frequencies[current_note.pitch] * (1 << current_note.octave) );
	}
	set_opts(STDFILE, REQUEST_RESET, 0);
}

void play_sound(char *argv[], int argc) {

	char songs[4096];
	song_t parsed_songs[20];
	int song_number = 0;
	int choice = -1;
	int i = 0;
	note_t current_note;
	uint32_t one_note_length;

	printf("Welcome to Sound Player 1.0\n");
	printf("Fetching sounds...\n");
	fgets(STDFILE, songs, 4096);

	printf("Parsing Sounds...\n");
	song_number = parse_sounds(songs, parsed_songs);

	printf("Available Tunes are: \n");
	for (int i = 0; i < song_number; i++) {
		printf("%d. %s\n", i+1, parsed_songs[i].title);
	}

	while (choice < 0) {

		printf("Insert a number from the list: ");
		scanf("%d", &choice);
		if (choice > song_number)
			choice = -1;
	}

	printf("Default Duration: %d\n", parsed_songs[choice-1].default_duration);
	printf("Default Octave: %d\n", parsed_songs[choice-1].default_octave);
	printf("Beat: %d\n", parsed_songs[choice-1].beat);

	printf("Read Notes: %d\n", parsed_songs[choice-1].read_notes);

	one_note_length = 60000 / parsed_songs[choice-1].beat * 4;

	for (; i < parsed_songs[choice-1].read_notes; i++) {

		current_note = parsed_songs[choice-1].notes[i];

		beepwo( one_note_length / current_note.duration,
			base_frequencies[current_note.pitch] * (1 << current_note.octave) );
	}
	set_opts(STDFILE, REQUEST_RESET, 0);

}

/*==========================================
--------   Auxiliary functions for commands
===========================================*/


static int parse_sounds(char* raw, song_t* parsed_songs) {

	uint8_t current_song = 0;
	char *start_song = raw;

	while (*raw != 0) {

		if (*raw == ';') {
			*raw = 0;
			parse_sound(start_song, &parsed_songs[current_song]);
			start_song = raw+1;
			current_song++;
		}

		raw++;
	}

	return current_song;
}

static void parse_sound(char *raw, song_t* parse_song) {

	uint8_t part = 0;
	char *start = raw;

	while (*raw != 0) {

		if (*raw == ':') {
			*raw = 0;
			if (part == 0) {
				parse_title(start, parse_song);
			} else if (part == 1) {
				parse_header(start, parse_song);
			}
			start = raw+1;
			part++;
		}

		raw++;
	}

	parse_body(start, parse_song);
}

static void parse_title(char *raw, song_t* parse_song) {
	// char title[30];
	uint8_t i = 0;

	while (*raw != 0) {

		parse_song->title[i++] = *raw;

		raw++;
	}
}

static void parse_header(char *raw, song_t* parse_song) {

	parse_song->default_duration = (uint8_t)(*(raw+2) - '0');
	parse_song->default_octave = (uint8_t)(*(raw+6) - '0');
	if (*(raw+12) == ':' || *(raw+12) == 0) {
			parse_song->beat = (uint16_t)(*(raw+10) - '0')*10+(uint16_t)(*(raw+11 ) - '0');
	}
	else {
		parse_song->beat = (uint16_t)(*(raw+10) - '0')*100+(uint16_t)(*(raw+11) - '0')*10+(uint16_t)(*(raw+12) - '0');
	}
}

static void parse_body(char *raw, song_t* parse_song) {

	NoteParserState state = kReadingInitial;
	uint8_t i = 0;

	do {

		switch (state) {
			case kReadingInitial:
				parse_song->notes[i].duration = (uint8_t)0;
				parse_song->notes[i].octave = (uint8_t)0;
				if ('1' <= *raw && *raw <= '9') {
					state = kReadingDuration;

					parse_song->notes[i].duration = (uint8_t)(*raw - '0');

				} else if ('a' <= *raw && *raw <= 'g') {

					state = kReadingPitch;

					parse_song->notes[i].duration = parse_song->default_duration;

					switch (*raw) {
						case 'a':
							parse_song->notes[i].pitch = NOTE_A;
							break;
						case 'b':
							parse_song->notes[i].pitch = NOTE_B;
							break;
						case 'c':
							parse_song->notes[i].pitch = NOTE_C;
							break;
						case 'd':
							parse_song->notes[i].pitch = NOTE_D;
							break;
						case 'e':
							parse_song->notes[i].pitch = NOTE_E;
							break;
						case 'f':
							parse_song->notes[i].pitch = NOTE_F;
							break;
						case 'g':
							parse_song->notes[i].pitch = NOTE_G;
							break;
						case 'p':
							parse_song->notes[i].pitch = NOTE_P;
							break;
					}

				}
				break;
			case kReadingDuration:
				if ('1' <= *raw && *raw <= '9') {

					parse_song->notes[i].duration = parse_song->notes[i].duration*10+(uint8_t)(*raw - '0');
				} else {
					state = kReadingPitch;
					switch (*raw) {
						case 'a':
							parse_song->notes[i].pitch = NOTE_A;
							break;
						case 'b':
							parse_song->notes[i].pitch = NOTE_B;
							break;
						case 'c':
							parse_song->notes[i].pitch = NOTE_C;
							break;
						case 'd':
							parse_song->notes[i].pitch = NOTE_D;
							break;
						case 'e':
							parse_song->notes[i].pitch = NOTE_E;
							break;
						case 'f':
							parse_song->notes[i].pitch = NOTE_F;
							break;
						case 'g':
							parse_song->notes[i].pitch = NOTE_G;
							break;
						case 'p':
							parse_song->notes[i].pitch = NOTE_P;
							break;
					}
				}
				break;
			case kReadingPitch:
				if (*raw == '#') {
					parse_song->notes[i].pitch += 1;
				} else if (*raw == '.') {
					parse_song->notes[i].duration *= 2;
				} else if ('0' <= *raw && *raw <= '9'){
					parse_song->notes[i].octave = (uint8_t)(*raw - '0');
					state = kReadingOctave;
				} else if (*raw == ',') {
					parse_song->notes[i].octave = parse_song->default_octave;
					state = kReadingOctave;
				}
				break;
			case kReadingOctave:
				state = kReadingInitial;
				if ( parse_song->notes[i].duration == (uint8_t)0) {
					parse_song->notes[i].duration = parse_song->default_duration;
				}
				if ( parse_song->notes[i].octave == (uint8_t)0) {
					parse_song->notes[i].octave = parse_song->default_octave;
				}
				i++;
				break;
		}

		raw++;
	} while (*raw != 0);

	parse_song->read_notes = i;

}

//Receives input string, parses it for a date, returns 1 if valid, 0 if not
int parse_date(char* date_string, int* days, int* months, int* years) {
	int len =0;
	len = strlen(date_string);
	if (len !=8) {
		return 0;
	}
	if (date_string[2]!= '/' || date_string[5] != '/') {
		return 0;	
	}
	//days
	if ( !is_num(date_string[0]) || !is_num(date_string[1])) {
		return 0;
	}
	//months
	if ( !is_num(date_string[3]) || !is_num(date_string[4]) ) {
		return 0;
	}
	//years
	if ( !is_num(date_string[6]) || !is_num(date_string[7]) ) {	
		return 0;
	}
	*days = ((int)date_string[0]-'0' )*10+(int)(date_string[1]-'0'); 
	*months = ((int)date_string[3]-'0' )*10+(int)(date_string[4]-'0');
	*years = ((int)date_string[6]-'0' )*10+(int)(date_string[7]-'0'); 	
	return valid_date(*days, *months, *years);

}

int parse_time(char* time_string, int* seconds, int* minutes, int* hours) {	
	int len =0;
	len = strlen(time_string);
	if (len !=8) {
		return 0;
	}
	if (time_string[2]!= ':' || time_string[5] != ':') {
		return 0;	
	}
	//seconds
	if ( !is_num(time_string[0]) || !is_num(time_string[1])) {
		return 0;
	}
	//minutes
	if ( !is_num(time_string[3]) || !is_num(time_string[4])) {
		return 0;
	}
	//hours
	if ( !is_num(time_string[6]) || !is_num(time_string[7])) {
		return 0;
	}
	*seconds = (time_string[0]-'0')*10 + (time_string[1]-'0');
	*minutes = (time_string[3]-'0')*10 + (time_string[4]-'0');
	*hours = (time_string[6]-'0')*10 + (time_string[7]-'0');
	return valid_time(*seconds, *minutes, *hours);
}


int is_num(char c) {
	if ( (c >= '0') && (c<= '9')) {
		return 1;
	}
	return 0;
}

int valid_time(int sec, int min, int hrs) {

	if ( sec >60 || sec < 0||
		min >60 || min < 0	||
		hrs >24 || sec < 0)
	{
		return 0;
	}
	return 1;
}

int valid_date(int day, int month, int year) {
	unsigned short monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month < 1 || day < 1 || month > 12){
		return 0;
	}
	if (is_leap_year(year) && month == 2) {
		monthlen[1]++;
	}
	if (day>monthlen[month-1] || day < 1) {
		return 0;
	}
	return 1;
}

int is_leap_year(int year) {
	return ((!(year%4) && (year%100)) || !(year%400));
}	


void getchar_cmd(char *argv[], int argc)  {
	printf("Please type in a character\n");
	char c = getc();
	printf("You pressed: %c\n", c);
}

void printf_cmd(char *argv[], int argc) {
	printf("Testing printf...\n\n");
	printf("Printing an integer: %d\n", 99);
	printf("Printing a string: %s\n", "This is a real cool string!");
	printf("Printing in uppercase hexadecimal notation: %x\n", 0x55fa);
	printf("Printing a single char: %c\n", 'z');
}

void scanf_cmd(char *argv[], int argc) {
	int n;
	char vec[SCANF_MAX_STR_BUFFER];

	printf("Welcome to scanf user test:\n ");
	printf("And so, the trial begins...\n");
	printf("Please type in a number: \n");
	scanf("%d", &n);
	printf("You typed in: %d\n\n", n);
	reset_vect(vec);
	
	printf("Trial number 2...type in a short text: ");
	scanf("%s", vec);
	printf("You typed in: %s\n\n", vec);
	reset_vect(vec);

	printf("Trial number 3...Please type in a single character: ");
	scanf("%c", vec);
	printf("\nYou typed: %c\n\n", vec[0]);
	reset_vect(vec);

	printf("And so, the final trial begins:\n");
	printf("Are you ready? Type in Y or N\n");
	scanf("%s", vec);
	reset_vect(vec);
	printf(" Actually your response was irrelevant, proceeding with last trial...\n ");
	printf("Type in string format, your credit card number followed by verification code\n" );
	scanf("%s", vec);
	printf("\nYour fake card data was: %s\n\n", vec);
	reset_vect(vec);
}

void reset_vect(char vec[]) {
	int i;
	for (i = 0; i < 50; i++ ) {
		vec[i] = 0;
	}
}

void help_error_print() {
	printf("\nInvoke help as follows: \"help \"command_name\"\".\nTo see list of available commands type \"commands\"\n");	
}


