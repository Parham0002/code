CC = gcc
CFLAGS = -Wpedantic -Wall -Wextra -Werror

BUILD_DIR = build

all: $(BUILD_DIR)
	@echo "==================== Targets ===================="
	@echo "==> test: to build and run tests"
	@echo "==> clean: to remove all build files"
	@echo "================================================"

test: $(BUILD_DIR) $(BUILD_DIR)/test 
	@./$(BUILD_DIR)/test && gcovr -r . --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/stdlib.o $(BUILD_DIR)/stack.o 
	$(CC) --coverage $^ -lunity -o $@

$(BUILD_DIR)/stack.o: stack/stack.c stack/stack.h test/stdlib.h
	$(CC) -c --coverage $(CFLAGS) $< -I./test -I./stack -o $@

$(BUILD_DIR)/test.o: test/test.c test/stdlib.h stack/stack.h
	$(CC) -c $(CFLAGS) $< -I./test -I./stack -o $@

$(BUILD_DIR)/stdlib.o: test/stdlib.c test/stdlib.h
	$(CC) -c $(CFLAGS) $< -I./test -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean test 

$(BUILD_DIR):
	mkdir -p $@