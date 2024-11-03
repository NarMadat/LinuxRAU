CXX = g++
CXXFLAGS = -Wall -std=c++20

all: redirect-cin

redirect-cin: redirect-cin.o
	$(CXX) $(CXXFLAGS) redirect-cin.o -o redirect-cin

redirect-cin.o: redirect-cin.cpp
	$(CXX) $(CXXFLAGS) -c redirect-cin.cpp -o redirect-cin.o

clear: 
	rm -f *.o redirect-cin

