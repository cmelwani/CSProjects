#
#  Makefile
#  COMP15
#  Fall 2019
#
#  Makefile for the planet-driver, LinkedList and Planet
#

CXX      = clang++
CXXFLAGS = -Wall -Wextra -g -std=c++11
LDFlagS  = -g


planet-driver: planet-driver.o Planet.o LinkedList.o
	$(CXX) -o planet-driver planet-driver.o Planet.o LinkedList.o

#
# Only listing dependencies here
# make has a default rule that knows how to build a .o
# file from a .cpp file using $(CXX) and $(CXXFLAGS)
#
planet-driver.o:  planet-driver.cpp LinkedList.h
LinkedList.o:     LinkedList.cpp LinkedList.h Planet.h
Planet.o:         Planet.cpp Planet.h


clean:
	rm -f *.o core* *~ planet-driver
