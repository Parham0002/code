/*Make a function to count number of digits of a given integer number using recursion.
For example: 456 has 3 digits
Make a function to calculate XY using recursion. X and Y are two integers.
For example: 23 = 8.
 */

#include <iostream>
#include <limits>
#include <cmath>

// Function to count the number of digits in a number using recursion
int countnum(int number)
{
    number = std::abs(number); // Handle negative numbers
    if (number < 10)
    {
        return 1; // Base case: single-digit number
    }
    return 1 + countnum(number / 10); // Recursive case
}

// Function to calculate X^Y using recursion
int power(int x, int y)
{
    if (y == 0)
    {
        return 1; // Base case: anything raised to the power of 0 is 1
    }
    return x * power(x, y - 1); // Recursive case
}

// Function to validate integer input
int getValidInt(const std::string &prompt)
{
    int num;
    while (true)
    {
        std::cout << prompt;
        std::cin >> num;

        // Check if input is valid
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
        else
        {
            return num; // Valid input
        }
    }
}

int main()
{
    int choice;

    // Validate menu choice
    choice = getValidInt("Choose an operation:\n"
                         "1. Count the number of digits in a number\n"
                         "2. Calculate X^Y\n"
                         "Enter your choice (1 or 2): ");

    if (choice == 1)
    {
        // Count digits
        int number = getValidInt("Enter a number to count its digits: ");
        int result = countnum(number);
        std::cout << "The number " << number << " has " << result << " digit(s)." << std::endl;
    }
    else if (choice == 2)
    {
        // Calculate power
        int x = getValidInt("Enter the base (X): ");
        int y = getValidInt("Enter the exponent (Y): ");
        if (y < 0)
        {
            std::cout << "Exponent cannot be negative. Please restart the program and try again.\n";
            return 0;
        }
        int result = power(x, y);
        std::cout << x << " raised to the power of " << y << " is " << result << "." << std::endl;
    }
    else
    {
        std::cout << "Invalid choice. Please restart the program and choose 1 or 2.\n";
    }

    return 0;
}
