# A Makefile to build and run the test

CC := gcc
CFLAGS := -Wall

LIB_DIR := ex1
TEST_DIR := test
BUILD_DIR := build
TEST_EXE := test

INCLUDES := $(addprefix -I./, $(LIB_DIR))

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/*.c) $(wildcard $(TEST_DIR)/*.c))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(OBJECTS:.c=.o))

all: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "============ The Targets ============"
	@echo "==> clean: to clean"
	@echo "==> check: to run the test"
	@echo "====================================="

# -lm links the math library to the program.
$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -lunity -lm -o $@

# -g is used to compile for debugging
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	@$(CC) -MMD $(CFLAGS) -g -o $@ -c $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@$(CC) -MMD $(CFLAGS) -g -o $@ $(INCLUDES) -c $<

check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo ""
	@echo "======================================"
	@echo "=========== Run The Test ============="
	@echo "======================================"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE)

# Include the automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean check all

clean:
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@
