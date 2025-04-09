/**
 * @file exam.cpp
 * @author Parham Rezaei (mo.pr@outlook.com)
 * @brief Thread-safe Producer-Consumer implementation with Vehicle warehouse
 * This program implements a thread-safe producer-consumer pattern where:
 * - A producer thread manufactures vehicles (cars and trucks) and stores them in a warehouse
 * - Multiple consumer threads retrieve vehicles from the warehouse and display their properties
 * - The warehouse is implemented as a thread-safe circular buffer with synchronization
 * - Each vehicle has a unique ID, model, and type-specific properties
 * @version 0.1
 * @date 2025-04-09
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <chrono>
#include <memory>
#include <cstdlib>
#include <ctime>

#ifndef WAREHOUSEMAX
#define WAREHOUSEMAX 8
#endif

// check if warehouse is greater than 7 or not
static_assert(WAREHOUSEMAX > 7, "Werehouse need to be greater than 7");

// vehicle class
class vehicle
{
protected:
    static std::atomic<int> nextid;
    int id;
    std::string model;

public:
    vehicle(const std::string &model) : model(model)
    {
        id = nextid.fetch_add(1);
    }
    virtual ~vehicle() = default;

    int getid() const { return id; }
    std::string getmodel() const { return model; }

    virtual void print() const
    {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Model: " << model << std::endl;
    }
    virtual std::string gettype() const = 0;
};

// start the id from 1001
std::atomic<int> vehicle::nextid{1001};

// car class
class car : public vehicle
{
private:
    int maxpassenger;

public:
    car(const std::string &model, int maxpassenger)
        : vehicle(model), maxpassenger(maxpassenger) {}

    void print() const override
    {
        vehicle::print();
        std::cout << "Type: Car" << std::endl;
        std::cout << "Max Passenger: " << maxpassenger << std::endl;
    }

    std::string gettype() const override
    {
        return "car";
    }
};

// truck class
class truck : public vehicle
{
private:
    double maxweight;

public:
    truck(const std::string &model, double maxweight)
        : vehicle(model), maxweight(maxweight) {}

    void print() const override
    {
        vehicle::print();
        std::cout << "Type: Truck" << std::endl;
        std::cout << "Max Weight: " << maxweight << " ton's" << std::endl;
    }

    std::string gettype() const override
    {
        return "truck";
    }
};

// thread safe circular buffer
class warehouse
{
private:
    std::vector<std::shared_ptr<vehicle>> buffer;
    size_t capacity;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

    // make uncopyable
    warehouse(const warehouse &) = delete;
    warehouse &operator=(const warehouse &) = delete;

public:
    explicit warehouse(size_t capacity) : capacity(capacity)
    {
        buffer.resize(capacity);
    }

    void store(std::shared_ptr<vehicle> vehicle)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until there's space in the warehouse
        not_full.wait(lock, [this]()
                      { return count < capacity; });

        buffer[tail] = vehicle;
        tail = (tail + 1) % capacity;
        count++;

        // Notify consumers that a vehicle is available
        not_empty.notify_one();
    }

    std::shared_ptr<vehicle> reclaim()
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until there's a vehicle in the warehouse
        not_empty.wait(lock, [this]()
                       { return count > 0; });

        std::shared_ptr<vehicle> vehicle = buffer[head];
        buffer[head] = nullptr;
        head = (head + 1) % capacity;
        count--;

        // Notify producer that there's space available
        not_full.notify_one();

        return vehicle;
    }
};

// producer func
void producer(warehouse &warehouse, std::atomic<bool> &running)
{

    std::string car_models[] = {"Toyota", "Audi", "BMW"};
    std::string truck_models[] = {"Volvo", "Skania", "Vera"};

    while (running)
    {
        // Randomly create car or truck
        std::shared_ptr<vehicle> vehicle;

        // Random vehicle type (0 = car, 1 = truck)
        int type = rand() % 2;

        if (type == 0)
        {
            // Create car with random model and passenger capacity
            int model_idx = rand() % 3;
            int passengers = 2 + rand() % 6; // 2-7 passengers
            vehicle = std::make_shared<car>(car_models[model_idx], passengers);
        }
        else
        {
            // Create truck with random model and weight capacity
            int model_idx = rand() % 3;
            float weight = 1.0f + (rand() % 200) / 10.0f; // 1.0-21.0 tons
            vehicle = std::make_shared<truck>(truck_models[model_idx], weight);
        }

        warehouse.store(vehicle);

        // std::cout << "produced" << vehicle->gettype() << "with id" << vehicle->getid() << std::endl;

        // sleep for a random time to simulate diffrent product rate
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

// consumer func
void consumer(int id, warehouse &warehouse, std::atomic<bool> &running)
{
    while (running)
    {
        // Get vehicle from warehouse
        std::shared_ptr<vehicle> vehicle = warehouse.reclaim();

        // Print vehicle info
        std::cout << "========= Consumer " << id << " ========" << std::endl;
        vehicle->print();

        // Sleep for random time
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

int main(int argc, char *argv[])
{

    srand(time(nullptr)); // for random number generation

    int numconsumers = 2; // Default
    if (argc > 1)
    {
        numconsumers = std::max(2, std::stoi(argv[1])); // Ensure at least 2 consumers
    }

    std::cout << "Starting with " << numconsumers << " consumers and warehouse capacity of "
              << WAREHOUSEMAX << std::endl;

    // Create the warehouse
    warehouse warehouse(WAREHOUSEMAX);

    // Control flag for threads
    std::atomic<bool> running(true);

    // Create producer thread
    std::thread producerThread(producer, std::ref(warehouse), std::ref(running));

    // Create consumer threads
    std::vector<std::thread> consumerThreads;
    for (int i = 1; i <= numconsumers; ++i)
    {
        consumerThreads.emplace_back(consumer, i, std::ref(warehouse), std::ref(running));
    }

    // Join all threads
    producerThread.join();
    for (auto &thread : consumerThreads)
    {
        thread.join();
    }

    std::cout << "Simulation ended." << std::endl;

    return 0;
}