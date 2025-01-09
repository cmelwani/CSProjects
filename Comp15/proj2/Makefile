CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

findpath: main.o Location.o Graph.o
	$(CXX) -o $@ $^

clean:
	rm -f findpath *.o *.dSYM

provide:
	provide comp15 rt README Makefile Graph.cpp Graph.h main.cpp \
	testGraph.txt


# Add some rules for rt website
include Makefile.publish
