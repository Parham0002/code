cmake_minimum_required(VERSION 3.22)

project(button_tests C)

# Enable testing and coverage
enable_testing()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/button
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_button
    ${CMAKE_CURRENT_SOURCE_DIR}/unity
)

# Source files for the test
set(TEST_SOURCES
    test_button/test.c
    test_button/bsp.c       # test BSP (mock)
    ../lib/button/button.c  # actual code under test
    unity/unity.c           # Unity framework
)

# Create test executable
add_executable(test_runner ${TEST_SOURCES})

# Define this symbol so the test uses main() instead of app_main()
target_compile_definitions(test_runner PRIVATE RUNNING_ON_PC)

# Link with gcov for coverage
target_link_libraries(test_runner gcov)

# Register as a CTest
add_test(NAME button_test COMMAND test_runner)

# Add coverage report target (using gcovr)
find_program(GCOVR_PATH gcovr)
if (GCOVR_PATH)
    add_custom_target(coverage
    COMMAND ${GCOVR_PATH}
    -r ${CMAKE_SOURCE_DIR}/..
    --html --html-details
    -o coverage.html
    --exclude-unreachable-branches
    --exclude '.*unity.*'
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report with gcovr"
    )
else()
    message(WARNING "gcovr not found: coverage report will not be generated.")
endif()
