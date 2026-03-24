CXX = g++
CXXFLAGS = -Wall --std=c++17

all: MainProgram

MainProgram: MainProgram.cpp
	$(CXX) $(CXXFLAGS) -o MainProgram MainProgram.cpp

# Build test runner
test_runner: test.cpp MainProgram.cpp
	$(CXX) $(CXXFLAGS) -o test_runner test.cpp

# Run all tests
test: test_runner
	./test_runner

# Run specific test groups
temperature: test_runner
	./test_runner "[temperature]"

bank: test_runner
	./test_runner "[bank]"

password: test_runner
	./test_runner "[password]"

clean:
	rm -f MainProgram test_runner

.PHONY: all test clean temperature bank password
