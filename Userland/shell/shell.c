#include <shell.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <libc.h>
#include <command.h>


unsigned char listening_mouse = 1;

char shell_buffer[SHELL_BUFFER_SIZE];
int curr_pos = 0;

int history_index = 0, history_inserting_index;
history_entry cmd_history[100];

cmd_entry cmd_table[32];
int cmd_count = (sizeof(cmd_table) / sizeof(cmd_entry));

void init_shell() {

	clean_buffer();
	initialize_cmd_table();
	print_shell_text();
}

void print_shell_text() {
	printf(SHELL_TEXT);
}

void print_shell_error() {
	fprintf(STDERR, "We are sorry, \"%s\" command does not exist. \nFor full list of commands please type: \"commands\"\n", shell_buffer);
}

void update_shell() {
	char key;
	key = getc();

	refresh_shell(key);
}

void refresh_shell(char key) {

	if (key == 0) {
		return;
	}

	if (key == '\n') {
		putc('\n');
		shell_buffer[curr_pos] = 0;
		// push_history();
		history_inserting_index++;
		history_index = history_inserting_index;
		excecute_command(shell_buffer);
		print_shell_text();
		clean_buffer();

	} else if ( key == '\b' ) {
		if ( curr_pos > 0) {
			// putc('\b');
			// putc(' ');
			putc('\b');
			shell_buffer[--curr_pos] = '\0';
			cmd_history[history_inserting_index].buffer[curr_pos] = '\0';
		} else {
			make_beep();
		}

	} else if (curr_pos >= SHELL_BUFFER_SIZE-2) {
		//sound beep
		make_beep();
		return;

	} else {
		putc(key);
		shell_buffer[curr_pos] = key;
		cmd_history[history_inserting_index].buffer[curr_pos] = key;
		curr_pos++;
	}
}

void push_history() {
	while (cmd_history[history_index].buffer != 0)
		history_index++;
	history_index++;
}

void excecute_command(char* buffer) {
	int argc,
	cmd_len;
	char * args[64];

	int cmd_no = parse_command(buffer);
	if( cmd_no == -1) {
		print_shell_error();
		return;
	}

	cmd_len = strlen(cmd_table[cmd_no].name);
	argc = get_arguments(buffer + cmd_len, args);
	cmd_table[cmd_no].func(args, argc);
}

int parse_command(char* buffer) {
	int i = 0,
	cmd_no = -1;

	if(buffer[0] == '\0') {
		return -1;
	}

	while (cmd_no == -1 && i < cmd_count) {
		if (substr(cmd_table[i].name, buffer)) {
			cmd_no = i;
		}
		i++;
	}

	i = strlen(cmd_table[cmd_no].name);
	char next = buffer[i];

	if(next == ' ' || next == '\0'){
		return cmd_no;
	}

	return -1;
}



unsigned int get_arguments(char* buffer, char ** args) {
	int arg = 0,	// current argument
		i = 0;		// current buffer index

		char * ptr = NULL;

		while (buffer[i] != '\0' && buffer[i] == ' ') {
			i++;
		}

		while (buffer[i] != '\0' && arg < 64) {
		// guard condition
			if (buffer[i] == ' ') {
				ptr = NULL;
				buffer[i] = '\0';
				i++;
				continue;
			}

			if (ptr == NULL) {
				ptr = buffer + i;
				args[arg] = ptr;
				arg++;
			}

			i++;
		}
		return arg;
	}


void fill_buffer(char *s) {
	int i = 0;
	while (*s != 0) {
		shell_buffer[i++] = *s;
		s++;
	}
}

void fill_shell(char *s) {
	// int i = 0;
	clean_shell();
	while (*s != 0) {
		refresh_shell(*s);
		s++;
	}
}

void clean_buffer() {
	int i = 0;
	while(i < SHELL_BUFFER_SIZE && i < curr_pos) {
		shell_buffer[i] = '\0';
		i++;
	}
	curr_pos = 0;
}

void clean_shell() {
	int i = 0;
	int b_curr_pos = curr_pos;
	while(i < SHELL_BUFFER_SIZE && i < b_curr_pos) {
		refresh_shell('\b');
		i++;
	}
	// printf("curr pos at %d\n", curr_pos);
}

//Returns the index of the command in the command table, if such command does not exist, returns -1
int get_cmd_index(char * cmd_name)  {
	int i;
	for( i=0; i < cmd_count; i++) {
		if (strcmp(cmd_name, cmd_table[i].name) == 0) {
			return i;
		}
	}
	return -1;
}


cmd_entry* get_command_table() {
	return cmd_table;
}


//Prints list of available commands
void print_commands() {
	int i = 0;
	for( ; i < cmd_count && cmd_table[i].name != 0; i++) {
		printf("\t%s\n", cmd_table[i].name);
	}

}

void show_history() {
	int i = 0;
	for ( ; i < history_inserting_index; i++) {
		printf("%s\n", cmd_history[i].buffer);
	}
}

int get_cmd_count() {
	return cmd_count;
}

void initialize_cmd_table() {
	cmd_table[0].name = "echo";
	cmd_table[1].name = "clear";
	cmd_table[2].name = "date";
	cmd_table[3].name = "time";
	// cmd_table[4].name = "setdate";
	// cmd_table[5].name = "settime";
	// cmd_table[6].name = "getchar";
	// cmd_table[7].name = "printf";
	// cmd_table[8].name = "scanf";
	cmd_table[4].name = "man";
	cmd_table[5].name = "help";
	// cmd_table[12].name = "printascii";
	// cmd_table[13].name = "setcolor";
	cmd_table[6].name = "beep";
	cmd_table[7].name = "play_sound";
	cmd_table[8].name = "history";
	cmd_table[9].name = "hide_mouse";
	cmd_table[10].name = "show_mouse";
	cmd_table[11].name = "mouse_sensitivity";
	cmd_table[12].name = "mouse_test";
	cmd_table[13].name = "credits";
	cmd_table[14].name = "shutdown";
	cmd_table[15].name = "exit";

	cmd_table[0].func = &echo;
	cmd_table[1].func = &clear;
	cmd_table[2].func = &date;
	cmd_table[3].func = &time;
	// cmd_table[4].func = &set_date;
	// cmd_table[5].func = &settime;
	// cmd_table[6].func = &getchar_cmd;
	// cmd_table[7].func = &printf_cmd;
	// cmd_table[8].func = &scanf_cmd;
	cmd_table[4].func = &help;
	cmd_table[5].func = &commands;
	// cmd_table[12].func = &print_ascii_table;
	// cmd_table[13].func = &setcolor;
	cmd_table[6].func = &beep;
	cmd_table[7].func = &play_sound;
	cmd_table[8].func = &show_history;
	cmd_table[9].func = &mouse_hide;
	cmd_table[10].func = &mouse_show;
	cmd_table[11].func = &mouse_sensitivity;
	cmd_table[12].func = &mouse_test;
	cmd_table[13].func = &credits;
	cmd_table[14].func = &halt_system;
	cmd_table[15].func = &halt_system;

	cmd_table[0].help = "Echo repeats the input string following echo statement \n example: \"echo Hello I am using echo\"";
	cmd_table[1].help = "Clears the screen, uses no arguments, therefore will ignore any ones received\n";
	cmd_table[2].help = "Prints current system date on screen with format: \"dd/mm/yy\"\n";
	cmd_table[3].help = "Prints current system time on screenwith format: \"hs:mm:ss\"\n";
	// cmd_table[4].help = "Sets system date, format must be dd/mm/yyyy.\nExample: \"setdate 05/05/2015\"\n";
	// cmd_table[5].help = "Sets system time, format must be ss:mm:hh.\n Example: \" settime 10:59:22\"\n";
	// cmd_table[6].help = "Test command for directive board to test getchar() functionality.\n";
	// cmd_table[7].help = "Test command for supreme leaders to test printf() functionality \n";
	// cmd_table[8].help = "Test command for the High Command to test scanf() functionality\n";
	cmd_table[4].help = "Displays information about following command, syntaxt: \"man \"command_name\"\"\n";
	cmd_table[5].help = "Displays list of available commands\n";
	// cmd_table[12].help = "Prints entire list of ascii characters in order\n";
	// cmd_table[13].help = "Sets the console color (duh)\n";
	cmd_table[6].help = "Beeps\n";
	cmd_table[7].help = "Plays Sound!\n";
	cmd_table[8].help = "Displays a record of all executed commands\n";
	cmd_table[9].help = "Hides the mouse cursor\n";
	cmd_table[10].help = "Shows the mouse cursor (enabled by default)\n";
	cmd_table[11].help = "Sets the sensitivity of the mouse (1-100)\n";
	cmd_table[12].help = "Probamos el mouse\n";
	cmd_table[13].help = "Los creditos\n";
	cmd_table[14].help = "Halts the system.\n";
	cmd_table[15].help = "Alias de Shutdown\n";
}

void history_go_back() {

	if (history_index > 0) {
		fill_shell(cmd_history[--history_index].buffer);
	}

}

void history_go_forward() {


	if (history_index < history_inserting_index) {
		fill_shell(cmd_history[++history_index].buffer);
	}

}

int mouse_event(event_id a, uint64_t x, uint64_t y, uint64_t flag) {

	if (listening_mouse) {

		if (flag & 0x1) {
			// Left Click
			history_go_back();
		}

		if (flag & 0x2) {
			// Right Click
			history_go_forward();
		}

		if (flag & 0x4) {
			// Middle Click
			if (*shell_buffer != 0)
				refresh_shell('\n');
		}

	} else {
		if (flag & 0x1) {
			unhang_click();
		}
	}

	

	return 0;
}

void set_listening_mouse(unsigned char b) {
	listening_mouse = b;
}
