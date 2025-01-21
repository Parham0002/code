/*
Make a template function named map to map a value in a range to a value in another range.
Type of the ranges shall be arithmetic types.
Example: 0.5f in the range of 0.0f and 3.3f is mapped to 155 in the range of 0 and 1023*/
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
map(T value, T in_min, T in_max, T out_min, T out_max)
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Example usage
#include <iostream>

int main()
{
    float value = 0.5f;
    float in_min = 0.0f, in_max = 3.3f;
    float out_min = 0.0f, out_max = 1023.0f;

    float mapped_value = map(value, in_min, in_max, out_min, out_max);
    std::cout << "Mapped value: " << mapped_value << std::endl;

    return 0;
}
