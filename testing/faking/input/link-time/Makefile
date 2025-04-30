CC = gcc
CFLAGS = -Wpedantic -Wextra -Wall -Werror 

BUILD_DIR = build

all: $(BUILD_DIR)
	@echo "================= Targets ================="
	@echo "==> main: to build and run main"
	@echo "==> test: to build and run test"
	@echo "==> clean: to clean the project"
	@echo "==========================================="

main: $(BUILD_DIR) $(BUILD_DIR)/main
	@./$(BUILD_DIR)/$@

$(BUILD_DIR)/main: src/main.c utility/utility.c utility/utility.h
	@$(CC) $(CFLAGS) src/main.c utility/utility.c -I./utility -o $@

test: $(BUILD_DIR) $(BUILD_DIR)/test
	@./$(BUILD_DIR)/$@ && gcovr -r . --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/utility.o $(BUILD_DIR)/stdio.o
	@$(CC) --coverage $^ -lunity -o $@

$(BUILD_DIR)/test.o: test/test.c test/stdio.h utility/utility.h
	@$(CC) -c $(CFLAGS) $< -I./utility -I./test -o $@

$(BUILD_DIR)/utility.o: utility/utility.c utility/utility.h test/stdio.h
	@$(CC) -c --coverage $(CFLAGS) $< -I./utility -I./test -o $@

$(BUILD_DIR)/stdio.o: test/stdio.c test/stdio.h
	@$(CC) -c $(CFLAGS) test/stdio.c -I./test -o $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean main test

$(BUILD_DIR):
	@mkdir -p $@