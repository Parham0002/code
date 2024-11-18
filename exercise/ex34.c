#include <stdio.h>
#include <stdbool.h>

int tavan(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}
int countDigits(int number)
{
    bool isnotzero = true;
    bool isZero = false;

    if (number == 0)
        return isZero;
    else
        return isnotzero + countDigits(number / 10);
}
int main()
{
    int base, exponent;
    int number;
    printf("Enter a base: ");
    scanf("%d", &base);

    printf("Enter a exponent: ");
    scanf("%d", &exponent);

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("%d^%d = %d\n", base, exponent, tavan(base, exponent));
    if (number == 0)
        printf("Number of digits in %d is 1\n", number);
    else
        printf("Number of digits in %d is %d\n", number, countDigits(number));

    return 0;
}
