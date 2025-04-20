CC := gcc
CFLAGS := -Wall

LIB_DIR := src
TEST_DIR := test
BUILD_DIR := build
TARGET_EXE := fizzbuzz
TEST_EXE := fizzbuzz_test

INCLUDES := -I./$(LIB_DIR)

# Find source files
SRC_FILES := $(wildcard $(LIB_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

# Objects for linking
OBJECTS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRC_FILES) $(TEST_FILES)))

# Default target: build everything
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET_EXE)

# Rule for building the main executable (fizzbuzz)
$(BUILD_DIR)/$(TARGET_EXE): $(BUILD_DIR)/main.o $(BUILD_DIR)/fizzbuzz.o
	$(CC) $(CFLAGS) $^ -o $@

# Rule for building the test executable (fizzbuzz_test) without main.o
$(BUILD_DIR)/$(TEST_EXE): $(BUILD_DIR)/fizzbuzz_test.o $(BUILD_DIR)/fizzbuzz.o
	$(CC) $(CFLAGS) $^ -lunity -lm -o $@

# Rule for compiling .c files from the src directory (fizzbuzz.c)
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	@$(CC) $(CFLAGS) -MMD -g -o $@ -c $< $(INCLUDES)

# Rule for compiling .c files from the test directory (fizzbuzz_test.c)
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@$(CC) $(CFLAGS) -MMD -g -o $@ -c $< $(INCLUDES)

# Check rule to run tests
check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "======================================"
	@echo "=========== Running the Test ========="
	@echo "======================================"
	@./$(BUILD_DIR)/$(TEST_EXE)

# Clean rule to delete all build files
clean:
	rm -rf $(BUILD_DIR)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@

.PHONY: clean check all
