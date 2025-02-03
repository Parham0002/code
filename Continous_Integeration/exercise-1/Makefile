# Directories
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib

# Subdirectories in lib
FIZZBUZZ_DIR = $(LIB_DIR)/fizzbuzz
UNITY_DIR = $(LIB_DIR)/unity

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the main program
$(BUILD_DIR)/app: $(BUILD_DIR)/fizzbuzz.o $(BUILD_DIR)/unity.o $(BUILD_DIR)/main.o
	g++ -o $(BUILD_DIR)/app $(BUILD_DIR)/fizzbuzz.o $(BUILD_DIR)/unity.o $(BUILD_DIR)/main.o

# Compile fizzbuzz.cpp
$(BUILD_DIR)/fizzbuzz.o: $(FIZZBUZZ_DIR)/fizzbuzz.cpp $(FIZZBUZZ_DIR)/fizzbuzz.h | $(BUILD_DIR)
	g++ -c $(FIZZBUZZ_DIR)/fizzbuzz.cpp -o $(BUILD_DIR)/fizzbuzz.o -I$(FIZZBUZZ_DIR)

# Compile unity.cpp
$(BUILD_DIR)/unity.o: $(UNITY_DIR)/unity.cpp $(UNITY_DIR)/unity.h $(UNITY_DIR)/unity_internals.h | $(BUILD_DIR)
	g++ -c $(UNITY_DIR)/unity.cpp -o $(BUILD_DIR)/unity.o -I$(UNITY_DIR)

# Compile main.cpp
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(FIZZBUZZ_DIR)/fizzbuzz.h $(UNITY_DIR)/unity.h $(UNITY_DIR)/unity_internals.h | $(BUILD_DIR)
	gcc -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o -I$(FIZZBUZZ_DIR) -I$(UNITY_DIR)

# Rule to run the main program
run: $(BUILD_DIR)/app
	$(BUILD_DIR)/app $(NUM)

# Rule to build and run tests
$(BUILD_DIR)/test: $(BUILD_DIR)/fizzbuzz.o $(BUILD_DIR)/unity.o $(BUILD_DIR)/test.o
	g++ -o $(BUILD_DIR)/test $(BUILD_DIR)/fizzbuzz.o $(BUILD_DIR)/unity.o $(BUILD_DIR)/test.o

# Compile test.cpp
$(BUILD_DIR)/test.o: $(TEST_DIR)/test.cpp | $(BUILD_DIR)
	gcc -c $(TEST_DIR)/test.cpp -o $(BUILD_DIR)/test.o -I$(FIZZBUZZ_DIR) -I$(UNITY_DIR)

check: $(BUILD_DIR)/test
	$(BUILD_DIR)/test

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)




