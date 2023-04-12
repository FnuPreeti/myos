#include "console.h"

int terminal_position = 0;

/*method to clear the terminal screen*/
void clear_terminal(){
	for(int i=0; i<VGA_TOTAL_BYTES; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0X07;
	}
}

/*method to handle new line character i.e. move cursor to new line*/
void handle_newline_character(){
	terminal_position = terminal_position + VGA_BYTES_PER_ROW - (terminal_position % (VGA_BYTES_PER_ROW));
}

/*method to handle all the special character cases*/
void handle_special_character(char c){
	switch(c){
		case '\n':
		handle_newline_character();
		break;
		
	}
}

/*method to check whether the character is special or not*/
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

/*method to print each character of string*/
void print_character(char c){
	if(is_special_character(c)){
		handle_special_character(c);
		return;	
	}
	VGA_BUFFER[terminal_position++] = c;
	VGA_BUFFER[terminal_position++] = 0X07;
}

/*method to print the string*/
void print_string(char* str){
	for(int i=0; str[i] != '\0'; i++){
		print_character(str[i]);
	}
}

void print_line(char* str){
	print_string(str);
	print_character('\n');
}


