#include "console.h"
#include "keyboard.h"
void main(){
	clear_terminal();
	
	//printInteger(876);
        while (1) {
        	output_prompt();
        	read_command();
        	if(exitLoop)
        		break;
                
        }

	return ;
}

