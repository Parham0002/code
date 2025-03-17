#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <chrono>
#include <stdexcept>

class stack
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int *arr;
    int top;
    int capacity;

public:
    stack(int size)
    {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }
    ~stack()
    {
        delete[] arr;
    }

    stack(const stack &) = delete;
    stack &operator=(const stack &) = delete;

    void push(int value)
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (top == capacity - 1)
        {
            throw std::runtime_error("Stack is full");
        }

        cv.wait(lock, [&]
                { return top < capacity - 1; });

        arr[++top] = value;
        std::cout << "Pushed " << value << " to stack" << std::endl;

        cv.notify_all();
    }

    int pop()
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (top < 0)
        {
            throw std::runtime_error("Stack is empty");
        }

        cv.wait(lock, [&]
                { return top >= 0; });

        int value = arr[top--];
        std::cout << "Popped " << value << " from stack" << std::endl;

        cv.notify_all();

        return value;
    }
};

void producer(stack &s, int id)
{
    for (int i = 0; i < 5; ++i)
    {
        s.push(id * 10 + i); // Push unique values
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void consumer(stack &s, int id)
{
    for (int i = 0; i < 5; ++i)
    {
        int value = s.pop(); 
        std::cout << "Consumer " << id << " popped: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
int main()
{
    stack s(5);

    std::thread producer1(producer, std::ref(s), 1);
    std::thread producer2(producer, std::ref(s), 2);
    std::thread consumer1(consumer, std::ref(s), 1);
    std::thread consumer2(consumer, std::ref(s), 2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    
    return 0;
}