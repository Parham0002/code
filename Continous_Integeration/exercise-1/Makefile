

# Rule to build the main program
build/app: build/fizzbuzz.o build/main.o
	g++ build/fizzbuzz.o build/main.o -o build/app

# Compile fizzbuzz.cpp
build/fizzbuzz.o: lib/fizzbuzz/fizzbuzz.cpp lib/fizzbuzz/fizzbuzz.h
	g++ -c lib/fizzbuzz/fizzbuzz.cpp -I./lib/fizzbuzz -o build/fizzbuzz.o


# Compile main.cpp
build/main.o: src/main.cpp lib/fizzbuzz/fizzbuzz.h
	g++ -c src/main.cpp -I./lib/fizzbuzz -o build/main.o

# Compile unity.cpp
build/unity.o: lib/unity/unity.cpp lib/unity/unity.h lib/unity/unity_internals.h 
	g++ -c lib/unity/unity.cpp -I,/lib/unity/ -o build/unity.o

# Rule to build and run tests
build/test: build/fizzbuzz.o build/unity.o build/test.o
	g++ -o build/test build/fizzbuzz.o build/unity.o build/test.o

# Compile test.cpp
build/test.o:  test/test.cpp 
	gcc -c test/test.cpp -o build/test.o -I./lib/fizzbuzz -I./lib/unity

# Rule to run the main program
run: build build/app
	@./build/app 

check: build build/test
	@./build/test

# Ensure the build directory exists
build:
	mkdir -p build

# Clean build directory
clean:
	rm -rf build




