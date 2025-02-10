/* #include "greet.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>

std::string greet(const std::string &name)
{
    if (name.empty())
    {
        return "Hello, my friend.";
    }

    // Handle names with commas
    size_t comma_pos = name.find(',');

    if (comma_pos != std::string::npos)
    {
        size_t second_comma_pos = name.find(',', comma_pos + 1);

        if (second_comma_pos != std::string::npos) // Handle three names
        {
            std::string name1 = name.substr(0, comma_pos);
            std::string name2 = name.substr(comma_pos + 1, second_comma_pos - comma_pos - 1);
            std::string name3 = name.substr(second_comma_pos + 1);

            // Trim spaces
            name1.erase(0, name1.find_first_not_of(" "));
            name1.erase(name1.find_last_not_of(" ") + 1);
            name2.erase(0, name2.find_first_not_of(" "));
            name2.erase(name2.find_last_not_of(" ") + 1);
            name3.erase(0, name3.find_first_not_of(" "));
            name3.erase(name3.find_last_not_of(" ") + 1);

            // Check if all names are capitalized
            if (std::all_of(name1.begin(), name1.end(), [](char c)
                            { return std::isupper(c); }) &&
                std::all_of(name2.begin(), name2.end(), [](char c)
                            { return std::isupper(c); }) &&
                std::all_of(name3.begin(), name3.end(), [](char c)
                            { return std::isupper(c); }))
            {
                return "HELLO " + name1 + ", " + name2 + ", AND " + name3 + "!";
            }

            // Default greeting for three names
            return "Hello, " + name1 + ", " + name2 + ", and " + name3 + ".";
        }
        else // Handle two names
        {
            std::string name1 = name.substr(0, comma_pos);
            std::string name2 = name.substr(comma_pos + 1);

            // Trim spaces
            name1.erase(0, name1.find_first_not_of(" "));
            name1.erase(name1.find_last_not_of(" ") + 1);
            name2.erase(0, name2.find_first_not_of(" "));
            name2.erase(name2.find_last_not_of(" ") + 1);

            // Check if both names are capitalized
            if (std::all_of(name1.begin(), name1.end(), [](char c)
                            { return std::isupper(c); }) &&
                std::all_of(name2.begin(), name2.end(), [](char c)
                            { return std::isupper(c); }))
            {
                return "HELLO " + name1 + " AND " + name2 + "!";
            }

            // Default greeting for two names
            return "Hello, " + name1 + " and " + name2 + ".";
        }
    }

    if (std::all_of(name.begin(), name.end(), [](char c)
                    { return std::isupper(c); }))
    {
        return "HELLO " + name + ".";
    }

    return "Hello, " + name + ".";
} */

#include "greet.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream> // For debugging

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
    {
        return ""; // String is all whitespace
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

std::string greet(const std::string &name)
{
    if (name.empty())
    {
        return "Hello, my friend.";
    }

    // Split names by comma
    std::vector<std::string> names;
    std::stringstream ss(name);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        token = trim(token);
        if (!token.empty())
        {
            names.push_back(token);
        }
    }

    if (names.empty())
    {
        return "Hello, my friend.";
    }

    // Separate normal and shouted names
    std::vector<std::string> normalNames, shoutedNames;
    for (const auto &n : names)
    {
        if (std::all_of(n.begin(), n.end(), [](unsigned char ch)
                        { return std::isupper(ch); }))
        {
            shoutedNames.push_back(n);
        }
        else
        {
            normalNames.push_back(n);
        }
    }

    // Generate greeting for normal names
    std::string normalGreeting;
    if (!normalNames.empty())
    {
        if (normalNames.size() == 1)
        {
            normalGreeting = "Hello, " + normalNames[0] + ".";
        }
        else if (normalNames.size() == 2)
        {
            normalGreeting = "Hello, " + normalNames[0] + " and " + normalNames[1] + ".";
        }
        else
        {
            std::ostringstream oss;
            for (size_t i = 0; i < normalNames.size(); ++i)
            {
                if (i > 0)
                    oss << (i == normalNames.size() - 1 ? ", and " : ", ");
                oss << normalNames[i];
            }
            normalGreeting = "Hello, " + oss.str() + ".";
        }
    }

    // Generate greeting for shouted names
    std::string shoutedGreeting;
    if (!shoutedNames.empty())
    {
        if (shoutedNames.size() == 1)
        {
            shoutedGreeting = "HELLO " + shoutedNames[0] + "!";
        }
        else if (shoutedNames.size() == 2)
        {
            shoutedGreeting = "HELLO " + shoutedNames[0] + " AND " + shoutedNames[1] + "!";
        }
        else
        {
            std::ostringstream oss;
            for (size_t i = 0; i < shoutedNames.size(); ++i)
            {
                if (i > 0)
                    oss << (i == shoutedNames.size() - 1 ? ", AND " : ", ");
                oss << shoutedNames[i];
            }
            shoutedGreeting = "HELLO " + oss.str() + "!";
        }
    }

    if (!normalGreeting.empty() && !shoutedGreeting.empty())
    {
        return normalGreeting + " AND " + shoutedGreeting;
    }
    return normalGreeting.empty() ? shoutedGreeting : normalGreeting;
}
