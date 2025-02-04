# Variables
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib

# Subdirectories for libraries
FIZZBUZZ_DIR = $(LIB_DIR)/fizzbuzz
UNITY_DIR = $(LIB_DIR)/unity

# Compiler and Flags
CXX = g++
CXXFLAGS = -I$(FIZZBUZZ_DIR) -I$(UNITY_DIR) -Wall -Wextra -g
CC = gcc
CFLAGS = -I$(FIZZBUZZ_DIR) -I$(UNITY_DIR) -Wall -Wextra -g

# Source Files
MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/test.cpp
FIZZBUZZ_SRC = $(FIZZBUZZ_DIR)/fizzbuzz.cpp
UNITY_SRC = $(UNITY_DIR)/unity.cpp

# Object Files
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o
FIZZBUZZ_OBJ = $(BUILD_DIR)/fizzbuzz.o
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Executables
MAIN_EXE = $(BUILD_DIR)/app
TEST_EXE = $(BUILD_DIR)/test

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Pattern Rule: Compile all .cpp files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(FIZZBUZZ_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build the main program
$(MAIN_EXE): $(FIZZBUZZ_OBJ) $(UNITY_OBJ) $(MAIN_OBJ)
	$(CXX) -o $(MAIN_EXE) $(FIZZBUZZ_OBJ) $(UNITY_OBJ) $(MAIN_OBJ)

# Build the test program
$(TEST_EXE): $(FIZZBUZZ_OBJ) $(UNITY_OBJ) $(TEST_OBJ)
	$(CXX) -o $(TEST_EXE) $(FIZZBUZZ_OBJ) $(UNITY_OBJ) $(TEST_OBJ)

# Run the main program
run: $(MAIN_EXE)
	$(MAIN_EXE)

# Run the test program
check: $(TEST_EXE)
	$(TEST_EXE)

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)
