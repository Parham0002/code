/*Make a function to count number of digits of a given integer number using recursion.
For example: 456 has 3 digits
Make a function to calculate XY using recursion. X and Y are two integers.
For example: 23 = 8.
 */

#include <iostream>
#include <limits>

void countnum(int number)
{
    int count = 0;
    int temp = number;

    if (temp == 0)
    {
        count = 1;
    }
    else
    {
        while (temp != 0)
        {
            temp /= 10;
            ++count;
        }
    }
    std::cout << "The number " << number << " has " << count << " digit(s)." << std::endl;
}
int main()
{
    int num;

    std::cout << "Write a number to count its number of digits: ";
    while (true)
    {
        std::cin >> num;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer: ";
        }
        else
        {
            break;
        }
    }

    countnum(num);

    return 0;
}
