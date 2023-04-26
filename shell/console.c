#include "console.h"

int terminal_position = 0;
char character_buffer[50] = {0};
char command_buffer[2][200] = {0};
char charbuffer[200] = {'\0'};
int loopExit = 0;
Color font_color = LIGHT_GRAY;

void clear_terminal(){
	for(int i=0; i<VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = font_color;
	}
	terminal_position = 0;
	update_cursor();
}

void handle_special_character(char c){
	switch(c){
		case '\n':
		terminal_position = terminal_position+VGA_BYTES_PER_ROW-(terminal_position%(VGA_BYTES_PER_ROW));
		break;
		case ' ':
		terminal_position=terminal_position+2;
		break;
		default:
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = font_color;
		
	}
}

int is_special_character(char c) {
	if(c >= '0' && c <= '9'){
    		return  0;
	}else if(c >= 'A' && c <= 'Z'){
    		return  0;
    	}else if(c >= 'a' && c <= 'z'){
    		return  0;
    	}else{
    		return 1;
    	} 
}
void print_character(char c){
	if(terminal_position >= VGA_WIDTH * VGA_HEIGHT * 2)
		terminal_up();
	if(is_special_character(c)){
		handle_special_character(c);
	}else{
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = font_color;
	}
	update_cursor();
	return;
}

void print_string(char* str){
	for(int i=0; str[i] != '\0'; i++){
		print_character(str[i]);
	}
}

void print_line(char* str){
	print_string(str);
	print_character('\n');
}

uint16_t get_cursor_position(){
	uint16_t cursor_position=0;
	outb(0x3D4, 0x0F);
	cursor_position |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	cursor_position |= ((uint16_t)inb(0x3D5)) << 8;
	return cursor_position;
}
void update_cursor(){
	uint16_t cursor_position = terminal_position >> 1;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(cursor_position));
	
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)(cursor_position >> 8));
}



void printInteger(int num){
	char* buffer = character_buffer;
	char* str = itoa(buffer, num);
	print_string(str);
}
void output_prompt(){
	print_string("~>");
}
void read_command(){
	int type = 1;
	unsigned char byte;
        while (type) {
                while (byte = scan()) {
                        if (byte == ENTER){
                        	split_command();
                        	handle_command();
                        	clear_buffer(command_buffer[1]);
                                 clear_buffer(charbuffer);
                        	type = 0;
                        }else{
                        	print_character(charmap[byte]);
                        	append(charbuffer, charmap[byte]);
                        }
                }
        }
}


void handle_command(){
	if(strcmp(command_buffer[1], "exit") == 0){
		print_string("\nExiting the terminal...\n");
		loopExit = 1;
	}
	else if(strcmp(command_buffer[1], "clear") == 0){
		clear_terminal();		
	}
	else if(strcmp(command_buffer[1], "help") == 0){
		print_string(help_list);		
	}
	else if(strcmp(command_buffer[1], "set-terminal-color") == 0){
		set_terminal_fcolor();
		print_string("\n");
	}
	else{
		print_string("\nCommand not found: ");
		print_string(command_buffer[1]);
		print_string("\n");
	}
}


void set_terminal_fcolor(){
	if(strcmp(command_buffer[2], "black") == 0){
		font_color = BLACK;
	}
	else if(strcmp(command_buffer[2], "blue") == 0){
		font_color = BLUE;
	}
	else if(strcmp(command_buffer[2], "green") == 0){
		font_color = GREEN;
	}
	else if(strcmp(command_buffer[2], "cyan") == 0){
		font_color = CYAN;
	}
	else if(strcmp(command_buffer[2], "red") == 0){
		font_color = RED;
	}
	else if(strcmp(command_buffer[2], "magenta") == 0){
		font_color = MAGENTA;
	}
	else if(strcmp(command_buffer[2], "brown") == 0){
		font_color = BROWN;
	}
	else if(strcmp(command_buffer[2], "lightgray") == 0){
		font_color = LIGHT_GRAY;
	}
	else if(strcmp(command_buffer[2], "darkgray") == 0){
		font_color = DARK_GRAY;
	}
	else if(strcmp(command_buffer[2], "lightblue") == 0){
		font_color = LIGHT_BLUE;
	}
	else if(strcmp(command_buffer[2], "lightgreen") == 0){
		font_color = LIGHT_GREEN;
	}
	else if(strcmp(command_buffer[2], "lightcyan") == 0){
		font_color = LIGHT_CYAN;
	}
	else if(strcmp(command_buffer[2], "lightred") == 0){
		font_color = LIGHT_RED;
	}
	else if(strcmp(command_buffer[2], "lightmagenta") == 0){
		font_color = LIGHT_MAGENTA;
	}
	else if(strcmp(command_buffer[2], "yellow") == 0){
		font_color = YELLOW;
	}
	else if(strcmp(command_buffer[2], "white") == 0){
		font_color = WHITE;
	}
	else{
		print_string("\nNo Color FOUND...\n");
	}
}


void terminal_up()
{
    copy_content((char *) (getoff(0,1) + VGA_BUFFER), (char *) (getoff(0,0) + VGA_BUFFER), VGA_WIDTH * (VGA_HEIGHT - 1) * 2);

    for(int column = 0; column < VGA_WIDTH; column++)
    {
        terminal_position = getoff(column, VGA_HEIGHT - 1);
        print_character(0);
    }
    terminal_position = getoff(0, VGA_HEIGHT-1);
}


void split_command(){
	char delim = ' ';
	static char* input = 0;
	input = charbuffer;
	
	int i = 0, j = 0;
	for (; input[i] != '\0' && input[i] != ' '; i++){				
		command_buffer[1][i] = input[i];
	}
    	command_buffer[1][i] = '\0';
    	if(input[i] != '\0' && input[i+1] != ' '){
       		i++;
        	for(; input[i] != '\0' && input[i] != ' '; i++)
        	{
            		command_buffer[2][j] = input[i];
            		j++;
        	}
        	command_buffer[2][j] = '\0';
    	}
}

void copy_content(char * src, char * dest, int numbytes)
{  
    for(int i = 0; i < numbytes; i++)
    {
        *(dest + i) = *(src + i);
    }
}

int getoff( int col, int row)
{
    return 2 * (row * VGA_WIDTH + col);
}
