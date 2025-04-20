#include "fizzbuzz.h"
#include <stdio.h>

int main(void)
{
    int i;
    for (i = 1; i <= 20; i++)
    {
        printf("%s ", fizz_buzz(i));
    }
    return 0;
}
