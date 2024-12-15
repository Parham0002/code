/*
Make a program to read a number in the range of 0 and 255 from the standard input
and then print the binary form of the number to the output
While the enetered number is not in the range, the program shall ask for a new number.
Use the bitwise operators!
 */
#include <iostream>

int main()
{
    unsigned int num;
    std::cout << "enter your number between 0 to 255" << std::endl;
    std::cin >> num;

    while (num < 0 || num > 255)
    {
        std::cout << "error it has to be between 0 and 255" << std::endl;
        std::cin >> num;
    }
    std::cout << "binary of your number is :";
    for (int i = 7; i >= 0; i--)
    {
        std::cout << ((num >> i) & 1);
    }
    std::cout << std::endl;

    return 0;
}
