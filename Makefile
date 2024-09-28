CXX = g++
CXXFLAGS = -Wall -std=c++20

all: simple_copy

simple_copy: simple_copy.o
	$(CXX) $(CXXFLAGS) -o simple_copy simple_copy.o

simple_copy.o: simple_copy.cpp
	$(CXX) $(CXXFLAGS) -c simple_copy.cpp

clean:
	rm -f *.0 simple_copy
