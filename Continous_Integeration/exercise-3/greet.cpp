#include "greet.h"
#include <iostream>


std::string greet(const std::string &name)
{
    if (name.empty())
    {
        return "Hello, my friend.";
    }
    return "Hello, " + name + ".";
}
