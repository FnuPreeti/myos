#include "console.h"

int terminal_position = 0;
char character_buffer[60] = {0};

void clear_terminal(){
	for(int i=0; i<VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER; i=i+2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0X07;
	}
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
	if(is_special_character(c)){
		handle_special_character(c);
	}else{
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = 0X07;
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



void print_integer(int num){
	char* buffer = character_buffer;
	char* str = itoa(buffer, num);
	print_string(str);
}
