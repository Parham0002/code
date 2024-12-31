/*
Make a program to get a positive integer as an argument from the command line and then check if the number is prime or not.
*/

#include <iostream>
#include <cstdlib>

bool isprime(int number)
{
    if (number <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool isValidNumber(const char *str)
{
    while (*str)
    {
        if (!std::isdigit(*str))
        {
            return false;
        }
        ++str;
    }
    return true;
}

int main(int argc, char *argv[])
{
    bool success = true;
    int number = 0;
    // Check if a number is provided as a command-line argument
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <positive integer>" << std::endl;
        success = false;
    }
    else if (!isValidNumber(argv[1]))
    {
        std::cerr << "Error: Argument must be a positive integer." << std::endl;
        success = false;
    }
    else
    {
        // Convert the command-line argument to an integer
        number = std::atoi(argv[1]);
        if (number <= 0)
        {
            std::cerr << "Error: Please provide a positive integer greater than 0." << std::endl;
            success = false;
        }
    }

    if (success)
    {
        // Convert the command-line argument to an integer
        int number = std::atoi(argv[1]);

        // Validate the input
        if (number <= 0)
        {
            std::cerr << "Error: Please provide a positive integer." << std::endl;
            success = false;
        }
    }

    if (success)
    {
        // Check if the number is prime
        if (isprime(number))
        {
            std::cout << number << " is a prime number." << std::endl;
        }
        else
        {
            std::cout << number << " is not a prime number." << std::endl;
        }
    }
}