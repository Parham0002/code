#include "string.h"
#include <stdio.h>

static int lenght(char *str)
{
    int temp = 0;
    if (str == NULL)
    {
        temp = 0;
    }

    while (str[temp] != '\0')
    {
        temp++;
    }

    return temp;
}

int compare(char *str, char *str1)
{
    if (str != NULL && str1 != NULL)
    {
        if (lenght(str) == lenght(str1))
        {
            printf("strings are same size\n");
        }
        else
        {
            printf("strings are not same size\n");
        }
    }
}

int get_lenght(char *str)
{

    return lenght(str);
}