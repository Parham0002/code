cmake_minimum_required(VERSION 3.22.1)
project(QueueTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(QueueTest test_queue.cpp)
target_link_libraries(QueueTest GTest::GTest GTest::Main pthread)

# Add the test to CTest
add_test(NAME QueueTest COMMAND QueueTest)
