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
    std::condition_variable cv_push, cv_pop;
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
        if (top == capacity - 1)
        {
            throw std::runtime_error("Stack is full");
        }

        std::unique_lock<std::mutex> lock(mtx);
        cv_push.wait(lock, [this]
                     { return top < capacity - 1; });
        arr[++top] = value;
        std::cout << "Pushed " << value << " to stack" << std::endl;
        cv_push.notify_all();
    }

    int pop(int value)
    {
        if (top == -1)
        {
            throw std::runtime_error("Stack is empty");
        }
        std::unique_lock<std::mutex> lock(mtx);
        cv_pop.wait(lock, [this]
                    { return top >= 0; });
        std::cout << "Popped " << arr[top--] << " from stack" << std::endl;
        cv_pop.notify_all();
        return value;
    }
    friend std::ostream &operator<<(std::ostream &os, const stack &s)
    {
        os << "Stack: ";
        for (int i = 0; i <= s.top; i++)
        {
            os << s.arr[i] << " ";
        }
        return os;
    }

    int size() const
    {
        return top + 1;
    }

    bool empty() const
    {
        return top == -1;
    }

    bool full() const
    {
        return top == capacity - 1;
    }
};

void push_thread(stack &s){
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
void pop_thread(stack &s){
    for (int i = 0; i < 10; i++)
    {
        s.pop(i);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
int main()
{
    stack s(5);
    std::thread t1(push_thread, std::ref(s));
    std::thread t2(pop_thread, std::ref(s));
    t1.join();
    t2.join();
    return 0;
}
