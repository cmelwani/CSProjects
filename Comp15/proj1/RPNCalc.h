
/*
COMP15 Project 1
CHERYL MELWANI (cmelwa01)
27th February 2020
The RPNCalc.h is the h file that declares the RPNCalc class and its private
and public functions.
*/

#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include "DatumStack.h"
#include "Datum.h"
#include <cstdio>
#include <string>

using namespace std;

class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    void run();


private:
    DatumStack stack;

    bool got_int(string s, int *resultp);
    void runHelper(istream &input);
    void pushRunHelper(string query);
    string parseRString(istream &input);
    void notQuery();
    void printQuery();
    void clearQuery();
    void dropQuery();
    void dupQuery();
    void swapQuery();
    void operationQuery(string query);
    void equalQuery();
    void comparisonQuery(string query);
    void execQuery();
    void fileQuery();
    void ifQuery();
};

#endif
