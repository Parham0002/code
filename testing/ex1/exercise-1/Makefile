# The Makefile to build and run the test

CC := gcc
CFLAGS := -Wall

LIB_DIR := lib
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build

TEST_EXE := test
PROG_EXE := main

INCLUDES := $(addprefix -I./,$(wildcard $(LIB_DIR)/*))

TEST_OBJS := $(notdir $(wildcard $(LIB_DIR)/*/*.c) $(wildcard $(TEST_DIR)/*.c))
TEST_OBJS := $(addprefix $(BUILD_DIR)/,$(TEST_OBJS:.c=.o))

PROG_OBJS := $(notdir $(wildcard $(LIB_DIR)/fizzbuzz/*.c) $(wildcard $(SRC_DIR)/*.c))
PROG_OBJS := $(addprefix $(BUILD_DIR)/,$(PROG_OBJS:.c=.o))

all:
	@clear
	@echo "************ The Targets *********************"
	@echo "** clean: to clean"
	@echo "** check: to build and test the module"
	@echo "** run NUM=xxx: to build and run the program"
	@echo "**********************************************"

$(BUILD_DIR)/$(PROG_EXE): $(PROG_OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/$(TEST_EXE): $(TEST_OBJS)
	$(CC) $^ -o $@

LIB_SRC := $(LIB_DIR)/*
$(BUILD_DIR)/%.o: $(LIB_SRC)/%.c
# -MMD Generates the dependencies automatically. E.g. build/datetime.d
	$(CC) -MMD $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o : $(TEST_DIR)/%.c
	$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

run: $(BUILD_DIR) $(BUILD_DIR)/$(PROG_EXE)
	@./$(BUILD_DIR)/$(PROG_EXE) $(NUM)

check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_DIR)
	@echo ""
	@echo "**************************************"
	@echo "********** Run The Test **************"
	@echo "**************************************"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE)

# Include the automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean check run all

clean:
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@
