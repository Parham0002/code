#include "utility.h"
#include <stdio.h>  

// Real low-level functions to read/write a single character
extern int low_level_getchar(void);
extern int low_level_putchar(int c);

bool utility_string_read(char *str, size_t size)
{
    if (str == NULL || size == 0)
    {
        return false;
    }
    size_t i = 0;
    for (size_t i ; i < size - 1; ++i)
    {
        int c = low_level_getchar();
        if (c == '\n' || c == EOF)
        {
            break;
        }
        str[i] = (char)c;
    }
    str[i] = '\0';
    return true;
}

bool utility_string_write(const char *str)
{
    if (str == NULL)
    {
        return false;
    }
    while (*str)
    {
        if (low_level_putchar(*str++) == EOF)
        {
            return false;
        }
    }
    return true;
}

void utility_string_reverse(char *str)
{
    if (str == NULL)
        return;
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    for (size_t i = 0; i < len / 2; ++i)
    {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}
