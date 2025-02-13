CC=g++
CFLAGS=-std=c++14 -Wall 
SRC=test_CircularQueue.cpp
BIN=build/test_runner

all: test

test: $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lgtest -lpthread
	$(BIN)

clean:
	rm -rf build
