#include “s21_sting.h”
void *memset(void *str, int c, size_t n)
{
    size_t i = 0;
                     //нужно ли добавлять допустим *p=(char*)str ??
                     //или можно сразу использовать *str из функции ??
    while (n>0)
    {
        str[i]=c;
        i++;
    }
                        // функция не рабочая переделать 
                // наверное нужно что то вернуть
                // maybe return(*str[])- это тип я пытаюсь вернуть масив (-_-