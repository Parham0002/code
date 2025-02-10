cmake_minimum_required(VERSION 3.22.1)

project(example)

set(CMAKE_CXX_STANDARD 17)


add_executable(test test.cpp greet.cpp)
target_link_libraries(test PRIVATE gtest gtest_main)