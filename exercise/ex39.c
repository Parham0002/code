#include "ex39.h"

unsigned int gcd(unsigned int a, unsigned int b)
{

    while (b != 0)
    {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
unsigned int lcm(unsigned int a, unsigned int b)
{
    return (a / gcd(a, b)) * b;
}
void sort(char *str)
{
    int lenght = strlen(str);
    char temp;

    for (int i = 0; i < lenght - 1; i++)
    {
        for (int j = i + 1; j < lenght; j++)
        {
            if (tolower(str[i]) > tolower(str[j]) ||
                (tolower(str[i]) == tolower(str[j]) && str[i] > str[j]))
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}