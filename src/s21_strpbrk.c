#include "s21_srting.h"

char *strpbrk(const char *str1, const char *str2)

{
    unsigned int i = 0;// порбую альтернативу size_t
    unsigned int t = 0;

    while(str1[i])
    {
        while(str2[t])
        {
            if (str1[i] == str2[t])
                {
                    return(str[i]); // после ретерна функция завершается , теперь нужно обьяснить бинарные деревья 
                }
            t++;
        }
        i++;
    }
    return(NULL);
}
