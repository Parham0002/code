#include <iostream>
#include <ctime>

int main()
{
    unsigned int rndm;
    unsigned int guess;
    unsigned int size = 99;
    int maxatt = 10;
    int att = 0;
    int result;

    do
    {
        std::srand(std::time(NULL));
        rndm = std::rand() % 100;

        std::cout << "******************************************" << std::endl;
        std::cout << "************** Game Started **************" << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "I have chosed the number now guess the number between 0 and 99 and try to beat me. you have 10 tries" << std::endl;
        while (att < maxatt)
        {
            std::cout << "enter your guess:" << std::endl;
            std::cin >> guess;
            result = guess;

            if (result < 0 || result > 99)
            {
                std::cout << " error only numbers between 0 and 99!" << std::endl;
                while (getchar() != '\n')
                    ;
                continue;
            }
            att++;
            if (guess > rndm)
            {
                std::cout << "to high try again ,";
            }
            else if (guess < rndm)
            {
                std::cout << "to low try again ,";
            }
            else
            {
                std::cout << "wow you won the game the number was : " << rndm << std::endl;
                break;
            }
            if (att < maxatt)
            {
                std::cout << "come on you got " << maxatt - att << " attempts still left :" << std::endl;
            }
            else
            {
                std::cout << "nice try buddy you are out of attemps. the number i had was :" << rndm << std::endl;
            }
        }
    } while (att < maxatt);
    return 0;
}