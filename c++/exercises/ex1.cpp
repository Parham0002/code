#include <iostream>


int main(void)
{

#if !defined(NUMBER) || ((NUMBER != 8) && (NUMBER != 16))
// #error error number must be 8 or 16
#else
    std::cout << "the value of number is:" << NUMBER << std::endl;
#endif

    return 0;
}
