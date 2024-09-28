CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

target = read

all: $(target)

$(target): read.cpp
	$(CXX) $(CXXFLAGS) -o $(target) read.cpp

clean:
	rm -f $(target)
