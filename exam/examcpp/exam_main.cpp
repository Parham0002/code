/**
 * @file exam_main.cpp
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief This code is a uncopyable template circular buffer class that provides
 * a array of T whose lenght is N and have a functionn to read , write and clear the buffer and
 * have a fucntion to give you the number of elements and it checks if the buffer is full or not.
 * and we have used assertion.
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <cassert>
#include <type_traits>

// using template
template <typename T, size_t N>
class CircularBuffer
{
private:
    T buffer[N];
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    bool full = false;

public:
    CircularBuffer()
    {
        static_assert(N >= 4, "Buffer size must be at least 4"); // here we ensures that buffer is atleast 4
    }

    // Make the class uncopyable
    CircularBuffer(const CircularBuffer &) = delete;
    CircularBuffer &operator=(const CircularBuffer &) = delete;

    // function to clear buffer
    void clear()
    {
        head = tail = count = 0;
        full = false;
    }
    // function to read buffer
    T read()
    {
        if (count == 0)
        {
            throw std::runtime_error("buffer is empty");
        }
        T value = buffer[tail];
        tail = (tail + 1) % N;
        count--;
        full = false;
        return value;
    }
    // function to write buffer
    void write(const T &data)
    {
        buffer[head] = data;
        if (full)
        {
            tail = (tail + 1) % N;
        }
        else
        {
            count++;
            full = (count == N);
        }
        head = (head + 1) % N;
    }
    // function to get the size of buffer
    size_t size() const noexcept
    {
        return count;
    }
    // function to check if buffer is full
    bool isFull() const noexcept
    {
        return full;
    }
    // Overload ostream operator for printing the queue
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
        }
        return os << "]";
    }
};

// test function with assertion
void testcircularbuffer()
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

    // Test clear
    intBuffer.clear();
    assert(intBuffer.size() == 0);
    assert(!intBuffer.isFull());
}

int main()
{
    // calling the test fucntion
    testcircularbuffer();

    std::cout << "All test passed!" << std::endl;
    return 0;
}
