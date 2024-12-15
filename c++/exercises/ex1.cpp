#include <iostream>

#ifdef NUMBER
#if (NUMBER != 8) && (NUMBER != 16)
#error "error number must be 8 or 16"
#endif
#else
#define NUMBER 8
#endif

int main()
{
    std::cout << "the value of number is:" << NUMBER << std::endl;

    return 0;
}
