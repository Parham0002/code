#include <stdio.h>

int zarb(int a, int b);

int moghayese(int a, int b);

int main()
{

    int a = 5;
    int b = 4;

    // zarb(a, b);

    printf("%d\n", zarb(a, b));

    moghayese(a, b);

    return 0;
}

int zarb(int a, int b)
{

    int result;

    result = a * b;
    for (int i = 0; i < result; i++)
    {
        printf("%d\n", i);
    }
    return result;
}
int moghayese(int a, int b)
{
    if (a > b)
    {
        printf(" a is bigger than b\n");
    }
    else
    {
        printf("b is bigger than a\n");
    }
}
