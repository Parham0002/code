/*
Make a struct type named person_t which has, name, age and id members.
Make a program to create an array of 3 persons.
Then read 3 persons from the standard input and then sort the persons according thier ids,
and print the persons to the standard output. To sort and print use only pointers.
*/
#include <iostream>

int main()
{
    typedef struct
    {
        int age;
        int id;
        std::string name;
    } person_t;

    person_t arr[3];

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Enter name, age, and id for person " << i + 1 << ": ";
        std::cin >> arr[i].name >> arr[i].age >> arr[i].id;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2 - i; j++)
        {
            if ((arr + j)->id > (arr + j + 1)->id)
            {
                person_t temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Person " << i + 1 << ": "
                  << (arr + i)->name << " "
                  << (arr + i)->age << " "
                  << (arr + i)->id << std::endl;
    }

    return 0;
}