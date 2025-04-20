#include <stdio.h>
#include <stdlib.h>

const char *fizz_buzz(int n)
{
    static char result[16]; // make sure the buffer is big enough
    if (n % 3 == 0 && n % 5 == 0)
        return "FizzBuzz";
    if (n % 3 == 0)
        return "Fizz";
    if (n % 5 == 0)
        return "Buzz";
    snprintf(result, sizeof(result), "%d", n); // store number as string
    return result;
}
