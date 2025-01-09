# Comp 15: Data Structures
# Tufts University
# Makefile for Lab 1

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -g3
DEPS     = ArrayList.h

shop: main.o ArrayList.o
	$(CXX) -o shop main.o ArrayList.o 

main.o:       main.cpp      ArrayList.h
ArrayList.o:  ArrayList.cpp ArrayList.h

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o core* *~ shop
