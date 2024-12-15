/*
Make a program to read a number in the range of 0 and 255 from the standard input
 then print the hexadecimal form of the number to the output
 While the enetered number is not in the range, the program shall ask for a new number.
*/

#include <iostream>

int main()
{
    int answer;
    std::cout << "write your number to get the hex form :" << std::endl;

    std::cin >> answer;

    while (answer < 0 || answer > 255)
    {
        std::cout << "number has to be beetween 0 and 255 try again:" << std::endl;
        std::cin >> answer;
    }

    std::cout << "hexa decimal form for " << answer << " is :" << std::hex << answer << std::endl;

    return 0;
}
