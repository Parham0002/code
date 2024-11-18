#include <stdio.h>
#include <stdlib.h> // For using `atoi` to convert command line argument to integer

// Function to check if a number is prime
int isPrime(int number)
{
    if (number <= 1)
        return 0; // Numbers less than or equal to 1 are not prime
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
            return 0; // If number is divisible by any number other than 1 and itself, it's not prime
    }
    return 1; // Number is prime
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    { // Check if exactly one argument is provided
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    // Convert the command line argument to an integer
    int number = atoi(argv[1]);

    if (number <= 0)
    { // Check if the number is a positive integer
        printf("Please provide a positive integer.\n");
        return 1;
    }

    // Check if the number is prime and print the result
    if (isPrime(number))
        printf("%d is a prime number.\n", number);
    else
        printf("%d is not a prime number.\n", number);

    return 0;
}
