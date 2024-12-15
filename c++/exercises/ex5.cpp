/*
Make a program to fill a 10 elements int array with positive random numbers lessr than 100, then

Print the array to the output.
Sort the array ascending(from the smallest to the largest) and then
Print the sorted array to the output.*/

#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

int main()
{
    unsigned int numbers[10];

    std::srand(std::time(NULL));
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = std::rand() % 100;
    }
    std::cout << "The array filled with random numbers: {";
    for (int i = 0; i < 10; i++)
    {
        std::cout << numbers[i];
        if (i < 9)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    std::sort(numbers, numbers + 10);

    std::cout << "The sorted array: {";

    for (int i = 0; i < 10; i++)
    {
        std::cout << numbers[i];
        if (i < 9)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    return 0;
}