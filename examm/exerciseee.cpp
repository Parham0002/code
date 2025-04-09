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
#include <string>
#include <vector>

// Set warehouse capacity (should be > 7)
#define WAREHOUSE_SIZE 10

// Vehicle ID counter
int next_vehicle_id = 1001;

// Base Vehicle class
class Vehicle {
protected:
    int id;
    std::string model;

public:
    Vehicle(std::string m) {
        id = next_vehicle_id++;
        model = m;
    }

    virtual ~Vehicle() {}

    int getId() { return id; }
    std::string getModel() { return model; }

    virtual void printInfo() = 0;
    virtual std::string getType() = 0;
};

// Car class
class Car : public Vehicle {
private:
    int passengers;

public:
    Car(std::string model, int pass) : Vehicle(model) {
        passengers = pass;
    }

    void printInfo() override {
        std::cout << "Car ID: " << id << ", Model: " << model
                  << ", Max Passengers: " << passengers << std::endl;
    }

    std::string getType() override {
        return "Car";
    }
};

// Truck class
class Truck : public Vehicle {
private:
    float max_weight;

public:
    Truck(std::string model, float weight) : Vehicle(model) {
        max_weight = weight;
    }

    void printInfo() override {
        std::cout << "Truck ID: " << id << ", Model: " << model
                  << ", Max Load: " << max_weight << " tons" << std::endl;
    }

    std::string getType() override {
        return "Truck";
    }
};

// Warehouse class - circular buffer
class Warehouse {
private:
    Vehicle* buffer[WAREHOUSE_SIZE];
    int count;
    int in_pos;
    int out_pos;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

public:
    // No copy allowed
    Warehouse(const Warehouse&) = delete;
    Warehouse& operator=(const Warehouse&) = delete;

    Warehouse() {
        count = 0;
        in_pos = 0;
        out_pos = 0;

        // Initialize buffer
        for (int i = 0; i < WAREHOUSE_SIZE; i++) {
            buffer[i] = nullptr;
        }
    }

    ~Warehouse() {
        // Clean up any remaining vehicles
        for (int i = 0; i < WAREHOUSE_SIZE; i++) {
            if (buffer[i] != nullptr) {
                delete buffer[i];
            }
        }
    }

    // Add vehicle to warehouse
    void storeVehicle(Vehicle* v) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if warehouse is full
        while (count == WAREHOUSE_SIZE) {
            not_full.wait(lock);
        }

        // Store vehicle
        buffer[in_pos] = v;
        in_pos = (in_pos + 1) % WAREHOUSE_SIZE;
        count++;

        // Notify consumers
        not_empty.notify_one();
    }

    // Get vehicle from warehouse
    Vehicle* getVehicle() {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if warehouse is empty
        while (count == 0) {
            not_empty.wait(lock);
        }

        // Get vehicle
        Vehicle* v = buffer[out_pos];
        buffer[out_pos] = nullptr;
        out_pos = (out_pos + 1) % WAREHOUSE_SIZE;
        count--;

        // Notify producer
        not_full.notify_one();

        return v;
    }
};

// Producer function
void producerFunction(Warehouse* warehouse, bool* running) {
    std::string car_models[] = {"Toyota", "Honda", "Ford", "BMW", "Audi"};
    std::string truck_models[] = {"Volvo", "Mack", "Peterbilt", "Kenworth", "Freightliner"};

    while (*running) {
        // Randomly create car or truck
        Vehicle* vehicle;

        // Random vehicle type (0 = car, 1 = truck)
        int type = rand() % 2;

        if (type == 0) {
            // Create car with random model and passenger capacity
            int model_idx = rand() % 5;
            int passengers = 2 + rand() % 6;  // 2-7 passengers
            vehicle = new Car(car_models[model_idx], passengers);
        } else {
            // Create truck with random model and weight capacity
            int model_idx = rand() % 5;
            float weight = 1.0f + (rand() % 200) / 10.0f;  // 1.0-21.0 tons
            vehicle = new Truck(truck_models[model_idx], weight);
        }

        // Store in warehouse
        warehouse->storeVehicle(vehicle);

        std::cout << "Produced: " << vehicle->getType() << " (ID: " << vehicle->getId() << ")" << std::endl;

        // Sleep for random time (production rate)
        std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 400));
    }
}

// Consumer function
void consumerFunction(int id, Warehouse* warehouse, bool* running) {
    while (*running) {
        // Get vehicle from warehouse
        Vehicle* vehicle = warehouse->getVehicle();

        // Print vehicle info
        std::cout << "Consumer " << id << " received: ";
        vehicle->printInfo();

        // Delete vehicle after use
        delete vehicle;

        // Sleep for random time (consumption rate)
        std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 600));
    }
}

int main(int argc, char* argv[]) {
    // Seed random number generator
    srand(time(nullptr));

    // Get number of consumers from command line
    int num_consumers = 2;  // Default
    if (argc > 1) {
        num_consumers = std::stoi(argv[1]);
        if (num_consumers < 2) num_consumers = 2;  // Minimum 2 consumers
    }

    std::cout << "Starting with " << num_consumers << " consumers" << std::endl;
    std::cout << "Warehouse capacity: " << WAREHOUSE_SIZE << std::endl;

    // Create warehouse
    Warehouse warehouse;

    // Control flag for threads
    bool running = true;

    // Create producer thread
    std::thread producer(producerFunction, &warehouse, &running);

    // Create consumer threads
    std::vector<std::thread> consumers;
    for (int i = 1; i <= num_consumers; i++) {
        consumers.push_back(std::thread(consumerFunction, i, &warehouse, &running));
    }

    // Run for a while
    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    // Stop threads
    running = false;

    // Join threads
    producer.join();
    for (auto& t : consumers) {
        t.join();
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}


*/