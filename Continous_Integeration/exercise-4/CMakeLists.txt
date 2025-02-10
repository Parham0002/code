cmake_minimum_required(VERSION 3.22.1)
project(LinkedList)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
add_library(LinkedList STATIC LinkedList.cpp)

# Enable testing
enable_testing()

# Add GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(LinkedListTest LinkedListTest.cpp)
target_link_libraries(LinkedListTest LinkedList GTest::GTest GTest::Main)
