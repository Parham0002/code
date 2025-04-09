#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <random>
#include <chrono>
#include <memory>

#ifndef WAREHOUSE_CAPACITY
#define WAREHOUSE_CAPACITY 10 // Default capacity if not specified during compilation
#endif

// Ensure minimum capacity
static_assert(WAREHOUSE_CAPACITY > 7, "Warehouse capacity must be greater than 7");

// Base Vehicle class
class Vehicle
{
protected:
    static std::atomic<int> nextId;
    int id;
    std::string model;

public:
    Vehicle(const std::string &model) : model(model)
    {
        id = nextId.fetch_add(1);
    }

    virtual ~Vehicle() = default;

    int getId() const { return id; }
    std::string getModel() const { return model; }

    virtual void print() const
    {
        std::cout << "Vehicle ID: " << id << ", Model: " << model;
    }

    virtual std::string getType() const = 0;
};

std::atomic<int> Vehicle::nextId{1001}; // Start IDs from 1001

// Car class
class Car : public Vehicle
{
private:
    int maxPassengers;

public:
    Car(const std::string &model, int maxPassengers)
        : Vehicle(model), maxPassengers(maxPassengers) {}

    void print() const override
    {
        Vehicle::print();
        std::cout << ", Type: Car, Max Passengers: " << maxPassengers << std::endl;
    }

    std::string getType() const override
    {
        return "Car";
    }
};

// Truck class
class Truck : public Vehicle
{
private:
    double maxLoadWeight;

public:
    Truck(const std::string &model, double maxLoadWeight)
        : Vehicle(model), maxLoadWeight(maxLoadWeight) {}

    void print() const override
    {
        Vehicle::print();
        std::cout << ", Type: Truck, Max Load Weight: " << maxLoadWeight << " tons" << std::endl;
    }

    std::string getType() const override
    {
        return "Truck";
    }
};

// Thread-safe circular buffer warehouse
class Warehouse
{
private:
    std::vector<std::shared_ptr<Vehicle>> buffer;
    size_t capacity;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

    // Make warehouse uncopyable
    Warehouse(const Warehouse &) = delete;
    Warehouse &operator=(const Warehouse &) = delete;

public:
    explicit Warehouse(size_t capacity) : capacity(capacity)
    {
        buffer.resize(capacity);
    }

    void store(std::shared_ptr<Vehicle> vehicle)
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

    std::shared_ptr<Vehicle> retrieve()
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until there's a vehicle in the warehouse
        not_empty.wait(lock, [this]()
                       { return count > 0; });

        std::shared_ptr<Vehicle> vehicle = buffer[head];
        buffer[head] = nullptr;
        head = (head + 1) % capacity;
        count--;

        // Notify producer that there's space available
        not_full.notify_one();

        return vehicle;
    }
};

// Producer function
void producer(Warehouse &warehouse, std::atomic<bool> &running)
{
    // Random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vehicle_type_dist(0, 1); // 0 for Car, 1 for Truck
    std::uniform_int_distribution<> passengers_dist(1, 8);
    std::uniform_real_distribution<> weight_dist(1.0, 20.0);
    std::uniform_int_distribution<> model_dist(1, 5);
    std::uniform_int_distribution<> sleep_dist(100, 500); // milliseconds

    const std::string car_models[] = {"Sedan", "SUV", "Hatchback", "Coupe", "Convertible"};
    const std::string truck_models[] = {"Pickup", "Semi", "Dump", "Tanker", "Flatbed"};

    while (running)
    {
        // Create a random vehicle
        std::shared_ptr<Vehicle> vehicle;
        if (vehicle_type_dist(gen) == 0)
        {
            // Create a car
            vehicle = std::make_shared<Car>(
                car_models[model_dist(gen) - 1],
                passengers_dist(gen));
        }
        else
        {
            // Create a truck
            vehicle = std::make_shared<Truck>(
                truck_models[model_dist(gen) - 1],
                weight_dist(gen));
        }

        // Store the vehicle in the warehouse
        warehouse.store(vehicle);

        std::cout << "Produced " << vehicle->getType() << " with ID " << vehicle->getId() << std::endl;

        // Sleep for a random time to simulate different production rates
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

// Consumer function
void consumer(int id, Warehouse &warehouse, std::atomic<bool> &running)
{
    // Random sleep time to simulate different consumption rates
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleep_dist(200, 800); // milliseconds

    while (running)
    {
        // Retrieve a vehicle from the warehouse
        std::shared_ptr<Vehicle> vehicle = warehouse.retrieve();

        // Print consumer ID and vehicle details
        std::cout << "Consumer " << id << " got: ";
        vehicle->print();

        // Sleep for a random time to simulate different consumption rates
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

int main(int argc, char *argv[])
{
    // Parse number of consumers from command line
    int numConsumers = 2; // Default
    if (argc > 1)
    {
        numConsumers = std::max(2, std::stoi(argv[1])); // Ensure at least 2 consumers
    }

    std::cout << "Starting with " << numConsumers << " consumers and warehouse capacity of "
              << WAREHOUSE_CAPACITY << std::endl;

    // Create the warehouse
    Warehouse warehouse(WAREHOUSE_CAPACITY);

    // Control flag for threads
    std::atomic<bool> running(true);

    // Create producer thread
    std::thread producerThread(producer, std::ref(warehouse), std::ref(running));

    // Create consumer threads
    std::vector<std::thread> consumerThreads;
    for (int i = 1; i <= numConsumers; ++i)
    {
        consumerThreads.emplace_back(consumer, i, std::ref(warehouse), std::ref(running));
    }

    // Let the simulation run for a while
    std::cout << "Press Enter to stop the simulation..." << std::endl;
    std::cin.get();

    // Stop all threads
    running = false;

    // Join all threads
    producerThread.join();
    for (auto &thread : consumerThreads)
    {
        thread.join();
    }

    std::cout << "Simulation ended." << std::endl;

    return 0;
}

/*#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <random>
#include <memory>

#ifndef WAREHOUSE_CAPACITY
#define WAREHOUSE_CAPACITY 10
#endif

// Ensure minimum capacity
static_assert(WAREHOUSE_CAPACITY > 7, "Warehouse capacity must be greater than 7");

// Base Vehicle class
class Vehicle {
protected:
    static std::atomic<int> nextId;
    int id;
    std::string model;

public:
    Vehicle(const std::string& model) : model(model) {
        id = nextId.fetch_add(1);
    }
    virtual ~Vehicle() = default;

    virtual void print() const {
        std::cout << "ID: " << id << ", Model: " << model;
    }

    virtual std::string getType() const = 0;
};

std::atomic<int> Vehicle::nextId{1001};

// Car class
class Car : public Vehicle {
private:
    int maxPassengers;

public:
    Car(const std::string& model, int maxPassengers)
        : Vehicle(model), maxPassengers(maxPassengers) {}

    void print() const override {
        Vehicle::print();
        std::cout << ", Type: Car, Max Passengers: " << maxPassengers << std::endl;
    }

    std::string getType() const override { return "Car"; }
};

// Truck class
class Truck : public Vehicle {
private:
    double maxLoadWeight;

public:
    Truck(const std::string& model, double maxLoadWeight)
        : Vehicle(model), maxLoadWeight(maxLoadWeight) {}

    void print() const override {
        Vehicle::print();
        std::cout << ", Type: Truck, Max Load Weight: " << maxLoadWeight << " tons" << std::endl;
    }

    std::string getType() const override { return "Truck"; }
};

// Warehouse class (thread-safe circular buffer)
class Warehouse {
private:
    std::shared_ptr<Vehicle> buffer[WAREHOUSE_CAPACITY];
    int head = 0;
    int tail = 0;
    int count = 0;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

    // Make warehouse uncopyable
    Warehouse(const Warehouse&) = delete;
    Warehouse& operator=(const Warehouse&) = delete;

public:
    Warehouse() = default;

    void add(std::shared_ptr<Vehicle> vehicle) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this] { return count < WAREHOUSE_CAPACITY; });

        buffer[tail] = vehicle;
        tail = (tail + 1) % WAREHOUSE_CAPACITY;
        count++;

        not_empty.notify_one();
    }

    std::shared_ptr<Vehicle> get() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this] { return count > 0; });

        auto vehicle = buffer[head];
        head = (head + 1) % WAREHOUSE_CAPACITY;
        count--;

        not_full.notify_one();
        return vehicle;
    }
};

// Producer function
void producer(Warehouse& warehouse, bool& running) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 1);
    std::uniform_int_distribution<> passengers_dist(2, 8);
    std::uniform_real_distribution<> weight_dist(1.0, 10.0);

    const std::string car_models[] = {"Sedan", "SUV", "Hatchback"};
    const std::string truck_models[] = {"Pickup", "Semi", "Dump"};

    while (running) {
        std::shared_ptr<Vehicle> vehicle;

        if (type_dist(gen) == 0) {
            // Create a car
            int model_idx = gen() % 3;
            vehicle = std::make_shared<Car>(car_models[model_idx], passengers_dist(gen));
        } else {
            // Create a truck
            int model_idx = gen() % 3;
            vehicle = std::make_shared<Truck>(truck_models[model_idx], weight_dist(gen));
        }

        warehouse.add(vehicle);
        std::cout << "Produced: " << vehicle->getType() << std::endl;

        // Random production speed
        std::this_thread::sleep_for(std::chrono::milliseconds(100 + gen() % 300));
    }
}

// Consumer function
void consumer(int id, Warehouse& warehouse, bool& running) {
    std::random_device rd;
    std::mt19937 gen(rd());

    while (running) {
        auto vehicle = warehouse.get();

        std::cout << "Consumer " << id << " got: ";
        vehicle->print();

        // Random consumption speed
        std::this_thread::sleep_for(std::chrono::milliseconds(200 + gen() % 500));
    }
}

int main(int argc, char* argv[]) {
    int num_consumers = (argc > 1) ? std::max(2, std::stoi(argv[1])) : 2;

    std::cout << "Starting with " << num_consumers << " consumers and warehouse capacity of "
              << WAREHOUSE_CAPACITY << std::endl;

    Warehouse warehouse;
    bool running = true;

    // Start producer thread
    std::thread producer_thread(producer, std::ref(warehouse), std::ref(running));

    // Start consumer threads
    std::vector<std::thread> consumer_threads;
    for (int i = 1; i <= num_consumers; i++) {
        consumer_threads.emplace_back(consumer, i, std::ref(warehouse), std::ref(running));
    }

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    running = false;

    producer_thread.join();
    for (auto& t : consumer_threads) {
        t.join();
    }

    return 0;
}

*/