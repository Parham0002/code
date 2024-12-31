/*
Make a program to read a std::string from a terminal and then convert

the uppercase letters to lowercase and vice versa and

in the end print the string to the standard output.

To change and print the string use only pointers.
 */

#include <iostream>

int main()
{
    std::string input;
    std::cout << "write some letter in upper or lower case to swap them:";
    std::getline(std::cin, input);

    if (!input.empty() && std::isdigit(input[0]))
    {
        std::cerr << "It has to be letters." << std::endl;
        exit(1);
    }

    char *ptr = &input[0];
    while (*ptr != '\0')
    {
        if (std::islower(*ptr))
        {
            *ptr = std::toupper(*ptr);
        }
        else if (std::isupper(*ptr))
        {
            *ptr = std::tolower(*ptr);
        }
        ptr++;
    }

    std::cout << input << std::endl;

    return 0;
}