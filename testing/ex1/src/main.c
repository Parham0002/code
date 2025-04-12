#include <stdio.h>
#include "main.h"

void fizzbuzz(int n);

int main(void)
{
    int n;
    printf("choose a number:");
    scanf("%d", &n);
    fizzbuzz(n);
    return 0;
}

void fizzbuzz(int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (i % 3 == 0 && i % 5 == 0)
        {
            printf("FizzBuzz\n");
        }
        else if (i % 3 == 0)
        {
            printf("Fizz\n");
        }
        else if (i % 5 == 0)
        {
            printf("Buzz\n");
        }
        else
        {
            printf("%d\n", i);
        }
    }
}