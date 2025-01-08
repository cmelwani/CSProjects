###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
### 27th February 2020
### Author:  CHERYL MELWANI (cmelwa01)



##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##  --- Delete this comment and put appropriate comments in ---


##
## Here is a rule for compiling .cyl files for use in your testing
##
CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra
LDFLAGS  = -g3


INCLUDES = $(shell echo *.h)


%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

CalcYouLater: main.o Datum.o DatumStack.o RPNCalc.o
	${CXX} ${CXXFLAGS} -o CalcYouLater DatumStack.o Datum.o main.o RPNCalc.o

testDatumStack: DatumStack.o Datum.o testDatumStack.o
	${CXX} ${CXXFLAGS} -o testDatumStack DatumStack.o Datum.o \
	testDatumStack.o

testRPNCalc: testRPNCalc.o Datum.o DatumStack.o RPNCalc.o
	${CXX} ${CXXFLAGS} -o testRPNCalc Datum.o DatumStack.o RPNCalc.o \
	testRPNCalc.o

.PHONY: clean
clean:
	rm -f ${EXECS} *.o *.dSYM./

provide:
	provide comp15 proj1	DatumStack.h DatumStack.cpp testDatumStack.cpp \
							RPNCalc.h RPNCalc.cpp testRPNCalc.cpp main.cpp \
							README Makefile test_commands.txt fact.cyl \
							parser.cpp ParserTest.txt got_int.cpp

%.cylc:  %.cyl
	./cylc $^
