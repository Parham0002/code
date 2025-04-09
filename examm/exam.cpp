/**
 * @file exam.cpp
 * @author Parham Rezaei (mo.pr@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-04-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <random>
#include <chrono>
#include <memory>

#ifndef WEREHOUSEMAX
#define WEREHOUSEMAX 10
#endif

static_assert(WEREHOUSEMAX > 7, "Werehouse need to be greater than 7");

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
        std::cout << "vehicle Id:" << id << "Model:" << model;
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
        std::cout << ", type: car, max passenger " << maxpassenger << std::endl;
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
        std::cout << ", Type: Truck, Max Weight: " << maxweight << " kg's" << std::endl;
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
