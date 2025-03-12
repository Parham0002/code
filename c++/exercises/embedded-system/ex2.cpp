#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

constexpr int ONE{0};
constexpr int TWO{1};
constexpr int THREE{2};

static std::mutex mtx;
static std::condition_variable cv;
static volatile int one_two_three = ONE;

static void print_one(void)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []
                { return (one_two_three == ONE); });
        std::cout << "1-";
        one_two_three = TWO;
        cv.notify_all();
    }
}
static void print_two(void)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []
                { return (one_two_three == TWO); });
        std::cout << "2-";
        one_two_three = THREE;
        cv.notify_all();
    }
}

static void print_three(void)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []
                { return (one_two_three == THREE); });
        std::cout << "3" << std::endl;
        one_two_three = ONE;
        cv.notify_all();
    }
}

int main(void)
{
    std::thread thrd1{print_one};
    std::thread thrd2{print_two};
    std::thread thrd3{print_three};

    thrd1.join();
    thrd2.join();
    thrd3.join();

    return 0;
}