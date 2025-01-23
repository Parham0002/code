
#include <iostream>
#include <cassert>
#include <type_traits>

template <typename T, size_t N>
class CircularBuffer
{
    static_assert(N >= 4, "Buffer size must be at least 4");

private:
    T buffer[N];
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    bool full = false;

public:
    CircularBuffer() = default;

    // Make the class uncopyable
    CircularBuffer(const CircularBuffer &) = delete;
    CircularBuffer &operator=(const CircularBuffer &) = delete;

    void clear()
    {
        head = tail = count = 0;
        full = false;
    }

    T read()
    {
        if (count == 0)
        {
            throw std::runtime_error("Buffer is empty");
        }
        T value = buffer[tail];
        tail = (tail + 1) % N;
        count--;
        full = false;
        return value;
    }

    void write(const T &data)
    {
        buffer[head] = data;
        if (full)
        {
            tail = (tail + 1) % N;
        }
        head = (head + 1) % N;
        if (head == tail)
        {
            full = true;
        }
        if (!full)
        {
            count++;
        }
    }

    size_t size() const
    {
        return count;
    }

    bool isFull() const
    {
        return full;
    }

    // average function for arithmetic types
    template <typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type
    average() const
    {
        if (count == 0)
        {
            throw std::runtime_error("Buffer is empty");
        }
        double sum = 0;
        size_t current = tail;
        for (size_t i = 0; i < count; i++)
        {
            sum += buffer[current];
            current = (current + 1) % N;
        }
        return sum / count;
    }

    friend std::ostream &operator<<(std::ostream &os, const CircularBuffer &cb)
    {
        if (cb.count == 0)
        {
            return os << "[]";
        }
        os << "[";
        size_t current = cb.tail;
        for (size_t i = 0; i < cb.count; i++)
        {
            os << cb.buffer[current];
            if (i < cb.count - 1)
            {
                os << ", ";
            }
            current = (current + 1) % N;
        }
        return os << "]";
    }
};

// Test function
void testCircularBuffer()
{
    // Test integer buffer
    CircularBuffer<int, 4> intBuffer;

    assert(intBuffer.size() == 0);
    assert(!intBuffer.isFull());

    // Test writing
    intBuffer.write(1);
    intBuffer.write(2);
    assert(intBuffer.size() == 2);

    // Test reading
    assert(intBuffer.read() == 1);
    assert(intBuffer.size() == 1);

    // Test overwriting
    intBuffer.write(3);
    intBuffer.write(4);
    intBuffer.write(5);
    assert(intBuffer.isFull());

    // Test average (VG requirement)
    assert(intBuffer.average() == (2.0 + 3.0 + 4.0 + 5.0) / 4.0);

    // Test clear
    intBuffer.clear();
    assert(intBuffer.size() == 0);
    assert(!intBuffer.isFull());
}

int main()
{
    testCircularBuffer();
    std::cout << "All tests passed!" << std::endl;

    // Example usage
    CircularBuffer<int, 4> buffer;
    buffer.write(1);
    buffer.write(2);
    buffer.write(3);
    buffer.write(4);
    buffer.write(5); // This will overwrite 1

    std::cout << "Buffer contents: " << buffer << std::endl;
    std::cout << "Average: " << buffer.average() << std::endl;

    return 0;
}
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <iostream>
#include <type_traits>

template <typename T, size_t N>
class CircularBuffer
{
    static_assert(N >= 4, "Buffer size must be at least 4");

private:
    T buffer[N];
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    bool full = false;

public:
    CircularBuffer() = default;
    CircularBuffer(const CircularBuffer &) = delete;
    CircularBuffer &operator=(const CircularBuffer &) = delete;

    void clear();
    T read();
    void write(const T &data);
    size_t size() const;
    bool isFull() const;

    template <typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type
    average() const;

    friend std::ostream &operator<<(std::ostream &os, const CircularBuffer &cb);
};

#include "circular_buffer.tpp"

#endif

template <typename T, size_t N>
void CircularBuffer<T, N>::clear()
{
    head = tail = count = 0;
    full = false;
}

template <typename T, size_t N>
T CircularBuffer<T, N>::read()
{
    if (count == 0)
    {
        throw std::runtime_error("Buffer is empty");
    }
    T value = buffer[tail];
    tail = (tail + 1) % N;
    count--;
    full = false;
    return value;
}

template <typename T, size_t N>
void CircularBuffer<T, N>::write(const T &data)
{
    buffer[head] = data;
    if (full)
    {
        tail = (tail + 1) % N;
    }
    head = (head + 1) % N;
    if (head == tail)
    {
        full = true;
    }
    if (!full)
    {
        count++;
    }
}

template <typename T, size_t N>
size_t CircularBuffer<T, N>::size() const
{
    return count;
}

template <typename T, size_t N>
bool CircularBuffer<T, N>::isFull() const
{
    return full;
}

template <typename T, size_t N>
template <typename U>
typename std::enable_if<std::is_arithmetic<U>::value, double>::type
CircularBuffer<T, N>::average() const
{
    if (count == 0)
    {
        throw std::runtime_error("Buffer is empty");
    }
    double sum = 0;
    size_t current = tail;
    for (size_t i = 0; i < count; i++)
    {
        sum += buffer[current];
        current = (current + 1) % N;
    }
    return sum / count;
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const CircularBuffer<T, N> &cb)
{
    if (cb.count == 0)
    {
        return os << "[]";
    }
    os << "[";
    size_t current = cb.tail;
    for (size_t i = 0; i < cb.count; i++)
    {
        os << cb.buffer[current];
        if (i < cb.count - 1)
        {
            os << ", ";
        }
        current = (current + 1) % N;
    }
    return os << "]";
}

#include <cassert>
#include "circular_buffer.h"

void testCircularBuffer()
{
    CircularBuffer<int, 4> intBuffer;

    assert(intBuffer.size() == 0);
    assert(!intBuffer.isFull());

    intBuffer.write(1);
    intBuffer.write(2);
    assert(intBuffer.size() == 2);

    assert(intBuffer.read() == 1);
    assert(intBuffer.size() == 1);

    intBuffer.write(3);
    intBuffer.write(4);
    intBuffer.write(5);
    assert(intBuffer.isFull());

    assert(intBuffer.average() == (2.0 + 3.0 + 4.0 + 5.0) / 4.0);

    intBuffer.clear();
    assert(intBuffer.size() == 0);
    assert(!intBuffer.isFull());
}

int main()
{
    testCircularBuffer();
    std::cout << "All tests passed!" << std::endl;

    CircularBuffer<int, 4> buffer;
    buffer.write(1);
    buffer.write(2);
    buffer.write(3);
    buffer.write(4);
    buffer.write(5);

    std::cout << "Buffer contents: " << buffer << std::endl;
    std::cout << "Average: " << buffer.average() << std::endl;

    return 0;
}
