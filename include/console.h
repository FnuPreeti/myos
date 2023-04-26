#include "stdint.h"
#include "portmap.h"
#include "lib.h"
#include "string.h"
#include "keyboard.h"
#ifndef H_CONSOLE
#define H_CONSOLE
static char* const VGA_BUFFER = (char*) 0xb8000;
extern int terminal_position;
extern char character_buffer[50];
extern char command_buffer[2][200];
extern char charbuffer[200];
extern int loopExit;

typedef enum {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
} Color;


#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define ENTER 0x1C
void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);
void update_cursor();
uint16_t get_cursor_position();
void printInteger(int num);
void output_prompt();
void read_command();
void handle_command();

void set_terminal_fcolor();
void split_command();
void copy_content(char* src, char* dest, int numbytes);
int getoff(int row, int col);
void terminal_up();

static char* const help_list = 
	"\nset-terminal-font-color: \n"
        "set terminal font color will set the color of the terminals font.\n"
        "It takes one argument: set-terminal-font-color (color).\n"
        "\nclear: \n"
        "clear will clear the terminal screen\n"
        "\n"
        "exit: \n"
        "exit will takes you out of the terminal\n"
        "\0";

#endif
