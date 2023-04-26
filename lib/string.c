#include "string.h"

int strcmp(char* str1, char* str2)
{
    while(*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
   
    return *str1 - *str2;
}

int strlen(char str[]){
	int length = 0;
	while(str[length] != '\0')
		length++;
		
	return length;
}

void append(char str[], char ch){
	int length = strlen(str);
	str[length] = ch;
	str[length + 1] = '\0';
}

void clear_buffer(char arry[]){
	int i = 0;
	while(arry[i] != '\0'){
		arry[i] = 0;
		i++;
	}
		
}
