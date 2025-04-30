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

test: $(BUILD_DIR) $(BUILD_DIR)/test
	@./$(BUILD_DIR)/$@ && gcovr -r . --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/utility.o $(BUILD_DIR)/console.o
	@$(CC) --coverage $^ -lunity -o $@

$(BUILD_DIR)/test.o: test/test.c test/console.h utility/utility.h
	@$(CC) -c $(CFLAGS) test/test.c -I./utility -o $@

$(BUILD_DIR)/utility.o: utility/utility.c test/console.h utility/utility.h
	@$(CC) -c --coverage $(CFLAGS) utility/utility.c -I./test -I./utility -o $@
	
$(BUILD_DIR)/console.o: test/console.c test/console.h
	@$(CC) -c $(CFLAGS) test/console.c -o $@

$(BUILD_DIR)/main: src/main.c utility/utility.c console/console.h utility/utility.h
	@$(CC) $(CFLAGS) src/main.c utility/utility.c -I./console -I./utility -o $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean main test

$(BUILD_DIR):
	@mkdir -p $@