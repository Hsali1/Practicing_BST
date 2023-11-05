CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = main.cpp BST.cpp

all: BST

BST: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o BST
	rm -f *.o

clean:
	rm -f BST
