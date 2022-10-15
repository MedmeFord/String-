#include “s21_string.h”

char *strcpy(char *dest, const char *src)
{
    s21_size_t i=0;
    while(src[i]!=0)
    {
        dest[i]=src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}