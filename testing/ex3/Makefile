# Path to  Unity source directory
UNITY_DIR := ~/code/unity

CC      := gcc
CFLAGS  := -I./src -I./test -I$(UNITY_DIR) -Wall -Wextra -g
SRC     := src/utility.c
TEST    := test/test_utility.c test/fakes_linktime.c
UNITY_C := $(UNITY_DIR)/unity.c

BUILD_DIR := build
OUT       := $(BUILD_DIR)/test_runner

all: build test

build:
	mkdir -p $(BUILD_DIR)

test: build
	$(CC) $(CFLAGS) \
	  $(SRC) $(TEST) $(UNITY_C) \
	  -o $(OUT)
	./$(OUT)

clean:
	rm -rf $(BUILD_DIR)
