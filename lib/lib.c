#include "lib.h"
char* itoa(char* str, int num)
{
    int base = 10;
    int i = 0;
    _Bool negative = 0;

    if(num == 0)
    {
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str;
    }
   
    if(num < 0)
    {
        negative = 1;
        num = -num;
    }

    while(num)
    {
        int rem = num % base;

        if(rem >= 10)
        {
            str[i++] = 'a' + (rem - 10);
        }
        else
        {
            str[i++] = '0' + rem;
        }

        num = num/base;
    }

    if(negative == 1)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    return reverse(str, 0, i - 1);

}
char* reverse(char* str, int start, int end)
{
    while (start < end)
    {
        swap(&str[start++], &str[end--]);
    }
    return str;
}

void swap(char* char1, char* char2)
{
    char t = *char1;
    *char1 = *char2;
    *char2 = t;
}

