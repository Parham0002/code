#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

constexpr int PING{0};
constexpr int PONG{1};
constexpr int ITRATIONS{10};

static void print_ping(void); // The ping thread function
static void print_pong(void); // The pong thread function

static std::mutex mtx;
static std::condition_variable cv;
static volatile int ping_pong = PING; // The shared variable

int main(void)
{
    // create the threads
    std::thread ping_thread{print_ping};
    std::thread pong_thread{print_pong};
    

    // wait on the threads to get completed
    ping_thread.join();
    pong_thread.join();

    return 0;
}
static void print_ping(void)
{
    for (int i = 0; i < ITRATIONS; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, []
                { return (ping_pong == PING); });

        std::cout << "Ping - ";
        ping_pong = PONG;

        lock.unlock();
        cv.notify_one();
    }
}

static void print_pong(void)
{
    for (int i = 0; i < ITRATIONS; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, []
                { return (ping_pong == PONG); });

        std::cout << "Pong" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ping_pong = PING;

        lock.unlock();
        cv.notify_one();
    }
}