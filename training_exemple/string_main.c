#include <stdio.h>
#include "string.h"

#define LEN 10

int main()
{

    char str[LEN] = "www";
    char str1[LEN] = "wdw";

    int len = get_lenght(str);

    printf("%d\n", len);

    compare(str, str1);

    return 0;
}