#include <mutex>
#include <thread>
#include <iostream>


constexpr int PING{0};
constexpr int PONG{1};


static void print_ping(void); 
static void print_pong(void); 

static std::mutex mtx;
static volatile int ping_pong = PING; 

static void print_ping(void)
{ 
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        while (ping_pong != PING)
        {
            ;
        }
        mtx.lock();
        std::cout << "Ping-";
        ping_pong = PONG;
        mtx.unlock();
    }
        }
static void print_pong(void)
{
    while (true)
    {
        
        while (ping_pong != PONG)
        {
            ;
        }
        mtx.lock();
        std::cout << "Pong" << std::endl;
        ping_pong = PING;
        mtx.unlock();
    }
}

int main(void){
    std::thread thrd1{print_ping};
    std::thread thrd2{print_pong};
    thrd1.join();
    thrd2.join();
    return 0;
}