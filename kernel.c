#include "console.h"
#include "keyboard.h"
void main(){
	clear_terminal();
	unsigned char byte;
	printInteger(878);
        while (1) {
                while (byte = scan()) {
                        
                        print_character(charmap[byte]);
                }
        }

	return ;
}

