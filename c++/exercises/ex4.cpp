/*
Read a lowercase letter from terminal and convert it to uppercase and then print the converted letter to the terminal.

Generate two random numbers and print them to the terminal.
*/
#include <iostream>
#include <string>
#include <time.h>

int main()
{
    std::string lowercase;
    std::cout << "write your letter: " << std::endl;
    std::cin >> lowercase;

    while (!isalpha(lowercase[0]))
    {
        std::cout << "wrong only letters. try again :" << std::endl;
        std::cin >> lowercase;
    }

    if (islower(lowercase[0]))
    {
        lowercase[0] = toupper(lowercase[0]);
        std::cout << lowercase << std::endl;
    }

    unsigned int number;
    srand(time(NULL));
    number = rand() % 100;

    std::cout << number << std::endl;

    return 0;
}