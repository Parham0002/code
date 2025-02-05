#include "greet.h"
#include <iostream>
#include <cctype>
#include <algorithm>

std::string greet(const std::string &name)
{
    if (name.empty())
    {
        return "Hello, my friend.";
    }

    size_t comma_pos = name.find(',');
    if (comma_pos != std::string::npos)
    {
        std::string name1 = name.substr(0, comma_pos);  
        std::string name2 = name.substr(comma_pos + 1); 

        
        name2.erase(0, name2.find_first_not_of(" "));
        name2.erase(name2.find_last_not_of(" ") + 1);

        return "Hello, " + name1 + " and " + name2 + ".";
    }

    if (!name.empty() && std::all_of(name.begin(), name.end(), [](char c) { return std::isupper(c); }))
    {
        return "HELLO " + name + ".";
    }

    
    return "Hello, " + name + ".";

  
}
