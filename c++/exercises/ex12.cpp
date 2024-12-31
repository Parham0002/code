/*
Make a program to read date and time from a terminal and then
check if the entered date and time is in the format of YYYY-MM-DD HH:mm:ss or not.
 */
#include <iostream>
#include <string>

bool validtime(const std::string &datetime);

int main()
{
    std::string input;
    do
    {
        std::cout << "Enter date and time in the format YYYY-MM-DD HH:mm:ss: ";
        std::getline(std::cin, input);
        if (validtime(input))
        {
            std::cout << "The entered date and time is in the correct format." << std::endl;
        }
        else
        {
            std::cout << "The entered date and time is NOT in the correct format." << std::endl;
        }

    } while (!validtime(input));

    return 0;
}
bool validtime(const std::string &datetime)
{
    bool isvalid = true;
    if (datetime.size() != 19)
    {
        isvalid = false;
    }
    if (datetime[4] != '-' || datetime[7] != '-' || datetime[10] != ' ' || datetime[13] != ':' || datetime[16] != ':')
    {
        isvalid = false;
    }
    for (int i = 0; i < datetime.size(); i++)
    {
        if ((i == 4 || i == 7 || i == 10 || i == 13 || i == 16))
        {
            continue;
        }
        if (!isdigit(datetime[i]))
        {
            isvalid = false;
            break;
        }
    }
    return isvalid;
}