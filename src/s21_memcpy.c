#include “s21_string.h”
void *s21_memcpy(void *dest, const void *src, s21_size_t n)
{
        *d = (char *) dest;
        *s = (char *) src;
        s21_size_t i = 0;
        while (i < n)
        {
                d[i] = s[i];
                i++;
        }
        return(d); // могу ли я вернуть dest ?
}