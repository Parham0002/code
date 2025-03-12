#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <chrono>

constexpr int ONE{0};
constexpr int TWO{1};
constexpr int THREE{2};

static std::mutex mtx;
static std::condition_variable cv;
static int number = ONE;

void print_numbers(int n)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [n]
                { return number == n; });

        switch (n)
        {
        case ONE:
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "1-";
            number = TWO;
            break;
        case TWO:
            std::cout << "2-";
            number = THREE;
            break;
        case THREE:
            std::cout << "3" << std::endl;
            number = ONE;
            break;
        default:
        std::cout << "Error" << std::endl;
            break;
        }

        lock.unlock();
        cv.notify_all();
    }
}int main(void)
{
    std::thread thrd1{print_numbers, ONE};
    std::thread thrd2{print_numbers, TWO};
    std::thread thrd3{print_numbers, THREE};
    thrd1.join();
    thrd2.join();
    thrd3.join();

    return 0;
}