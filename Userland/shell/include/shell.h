#ifndef __SHELL_H__
#define __SHELL_H__
#include <command.h>

#define SHELL_BUFFER_SIZE 128
#define SHELL_TEXT "Shell> "

typedef struct cmd_entry {
	char* name;
	char* help;
	void (*func)(char** argv, int argc);
} cmd_entry;

void init_shell(void);
void update_shell(void);
void excecute_command(char*);
int parse_command(char*);
void clean_buffer(void);
unsigned int get_arguments(char* buffer, char ** args);
int get_cmd_index(char *);
cmd_entry* get_command_table(void);
void print_commands(void);
int get_cmd_count(void);
void initialize_cmd_table(void);
void print_shell_text();
void print_shell_error();


#endif