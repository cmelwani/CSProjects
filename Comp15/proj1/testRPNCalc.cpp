

/*
COMP15 Project 1
CHERYL MELWANI (cmelwa01)
27th February 2020
The testRPNCalc.cpp tests all of the unit functions in the RPNCalc.cpp
*/


#include <iostream>
#include <sstream>
#include <string>
#include "RPNCalc.h"

using namespace std;

void pushAndPrintTest();
void notTest();
void clearTest();
void dropTest();
void dupTest();
void swapTest();
void operationsTest();
void comparisonsTest();
void execTest();
void fileTest();
void ifTest();

/* Purpose: Main calls the test functions */
int main() {
    pushAndPrintTest();
    notTest();
    clearTest();
    dropTest();
    dupTest();
    swapTest();
    operationsTest();
    comparisonsTest();
    execTest();
    fileTest();
    ifTest();

    return 0;
}

/* Purpose: Tests the functions in RPNCalc.cpp that pushes a Datum onto the
stack and also checks whether it prints it properly to terminal */
void pushAndPrintTest() {
    RPNCalc instance;
    cout << "PUSH/PRINT --- Should print out:\n" << "#f\n#t\n5\n{ 1 2 * }"
    << endl;
    cout << "PUSH/PRINT --- OUTPUT FROM CODE: " << endl;
    istringstream input("#f print #t print 5 print { 1 2 * } print");
    instance.runHelper(input);
}

/* Purpose: Tests the notQuery function in RPNCalc.cpp */
void notTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "NOT --- Should print out:\n" << "#f\nError: datum_not_bool"
    << endl;
    cout << "NOT --- OUTPUT FROM CODE: " << endl;
    istringstream input("#f #t not print 5 not");
    instance.runHelper(input);
}

/* Purpose: Tests the clearQuery function in RPNCalc.cpp */
void clearTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "CLEAR --- Should print out:\n" << "Error: empty stack" << endl;
    cout << "CLEAR --- OUTPUT FROM CODE: " << endl;
    istringstream input("clear print");
    instance.runHelper(input);
}

/* Purpose: Tests the dropQuery function in RPNCalc.cpp */
void dropTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "DROP --- Should print out:\n" << "5\nError: empty stack" << endl;
    cout << "DROP --- OUTPUT FROM CODE: " << endl;
    istringstream input("5 6 drop print drop print");
    instance.runHelper(input);
}

/* Purpose: Tests the dupQuery function in RPNCalc.cpp */
void dupTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "DUP --- Should print out:\n " << "Error: empty stack\n#t\n#t\n"
    << endl;
    cout << "DUP --- OUTPUT FROM CODE: " << endl;
    istringstream input("dup #f #t dup print drop print");
    instance.runHelper(input);
}

/* Purpose: Tests the swapQuery function in RPNCalc.cpp */
void swapTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "SWAP ---- Should print out:\n" <<
    "Error: empty stack\n5\n{ 1 2 / }\n" << endl;
    cout << "SWAP --- OUTPUT FROM CODE: " << endl;
    istringstream input("swap { 1 2 / } 5 print swap print");
    instance.runHelper(input);
}

/* Purpose: Tests the operationsQuery function in RPNCalc.cpp */
void operationsTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "OPERATIONS --- Should print out:\n" << "Error: empty stack\n30"
    << endl;
    cout << "Error: division by 0." << endl;
    cout << "13\n10\n0" << endl;
    cout << "Error: datum_not_int" << endl;
    cout << "OPERATIONS --- OUTPUT FROM CODE: " << endl;
    istringstream input("+");
    instance.runHelper(input);
    istringstream input1("5 6 * print 9 0 / 9 4 + print 3 - print 5 mod print");
    instance.runHelper(input1);
    istringstream input2("5 #t *");
    instance.runHelper(input2);
}

/* Purpose: Tests the comparisonsQuery function in RPNCalc.cpp */
void comparisonsTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "COMPARISONS --- Should print out:\n"
    << "Error: empty stack" << endl;
    cout << "Error: datum_not_int" << endl;
    cout << "#t\n#f\n#t\n#f\n#f\n#f\n#t" << endl;
    cout << "COMPARISONS --- OUTPUT FROM CODE: " << endl;
    istringstream input(">");
    instance.runHelper(input);
    istringstream input1("5 #t >");
    instance.runHelper(input1);
    istringstream input2("5 6 < print 1 2 > print 1 1 >= print 1 3 >= print");
    instance.runHelper(input2);
    istringstream input3("4 3 <= print");
    instance.runHelper(input3);
    istringstream input4("5 #t == print #t #t == print");
    instance.runHelper(input4);
}

/* Purpose: Tests the execQuery function in RPNCalc.cpp */
void execTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "COMPARISONS --- Should print out:\n"
    << "Error: empty stack" << endl;
    cout << "Error: cannot execute not rstring" << endl;
    cout << "2" << endl;
    cout << "{ 6 7 }\n4" << endl;
    cout << "COMPARISONS --- OUTPUT FROM CODE: " << endl;
    istringstream input("exec");
    instance.runHelper(input);
    istringstream input1("5 exec");
    instance.runHelper(input1);
    istringstream input2("{ 1 2 * } exec print");
    instance.runHelper(input2);
    istringstream input3("{ 1 4 { 6 7 } } exec print swap print");
    instance.runHelper(input3);
}

/* Purpose: Tests the fileQuery function in RPNCalc.cpp */
void fileTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "FILE -- Should print out:\n"
    << "Error: empty stack" << endl;
    cout << "Error: file operand not rstring" << endl;
    cout << "Unable to read exec.txt" << endl;
    cout << "1\n120" << endl;
    cout << "FILE --- OUTPUT FROM CODE: " << endl;
    istringstream input("file clear #t file clear { exec.txt } file ");
    instance.runHelper(input);
    istringstream input1("0 { fact.cylc } file print");
    instance.runHelper(input1);
    istringstream input2("5 { fact.cylc } file print");
    instance.runHelper(input2);
}

/* Purpose: Tests the ifQuery function in RPNCalc.cpp */
void ifTest() {
    RPNCalc instance;
    cout << "------------" << endl;
    cout << "IF -- Should print out:\n"
    << "Error: empty stack" << endl;
    cout << "Error: expected boolean in if test" << endl;
    cout << "Error: expected rstring in if branch" << endl;
    cout << "Error: expected rstring in if branch" << endl;
    cout << "12\n#f" << endl;
    cout << "IF --- OUTPUT FROM CODE: " << endl;
    istringstream input("if");
    instance.runHelper(input);
    istringstream input1("5 { 3 4 < } { #f } if");
    instance.runHelper(input1);
    istringstream input2("3 4 < 5 { 1 + 3 } if");
    instance.runHelper(input2);
    istringstream input3("3 4 < { 1 + 3 } 5 if");
    instance.runHelper(input3);
    istringstream input4(" 3 4 >= { 5 4 + } { 4 3 * } if print");
    instance.runHelper(input4);
    istringstream input5(" 3 4 < { #f } { #t } if print");
    instance.runHelper(input5);
}
