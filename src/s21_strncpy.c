#include “s21_string.h”
char *strncpy(char *dest, const char *src, s21_size_t n)
{
    s21_size_t i = 0;
    while(i!=n)
    {
        if(src == '/0')
        
            dest[i]='/0';
        
        else 
        {
            dest[i]=src[i];//am i can do it ?
        }
        i++;
    }
    return(dest);
}