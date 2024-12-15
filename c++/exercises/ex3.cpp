/*
Make a program to read a positive integer number from the standard input,
then sum all the even numbers from 0 to the entered number and print it to the output.

*/
#include <iostream>

int main()
{
    unsigned int number;
    unsigned int sum = 0;

    std::cout << "write your positive number to get the sum of all the even numbers :" << std::endl;
    std::cin >> number;

    for (unsigned int i = 0; i <= number; i += 2)
    {
        sum += i;
    }

    std::cout << "The sum of even numbers from 0 to " << number << " is: " << sum << std::endl;

    return 0;
}