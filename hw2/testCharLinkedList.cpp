/*
*
*  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
*
*  testCharLinkedList.cpp
*  Testing File for your sequence CharLinkedList class
*
*  Written by: Cheryl Melwani
*        UTLN: cmelwa01
*          on: Feb 4th 2020
*/

#include <iostream>
#include "CharLinkedList.h"
#include <stdexcept>


using namespace std;

void firstConstructorTesting();
void secondConstructorTesting();
void thirdConstructorTesting();
void copyConstructorTesting();
void assignmentOperatorTesting();
void isEmptyTesting();
void clearTesting();
void sizeTesting();
void insertAtTesting(); //elementAt and print testing as well
void insertInOrderTesting();
void firstTesting();
void lastTesting();
void elementAtTesting();
void pushAtBackTesting();
void pushAtFrontTesting();
void popFromFrontTesting();
void popFromBackTesting();
void removeAtTesting();
void replaceAtTesting();
void concatenateTesting();
void findTesting();

int main() {
    firstConstructorTesting();
    secondConstructorTesting();
    thirdConstructorTesting();
    copyConstructorTesting();
    assignmentOperatorTesting();
    isEmptyTesting();
    clearTesting();
    sizeTesting();
    insertAtTesting();
    insertInOrderTesting();
    pushAtBackTesting();
    popFromBackTesting();
    firstTesting();
    pushAtFrontTesting();
    popFromFrontTesting();
    elementAtTesting();
    lastTesting();
    removeAtTesting();
    replaceAtTesting();
    concatenateTesting();
    findTesting();
}

/* Tests nullary constructor */
void firstConstructorTesting() {
    cout << "****** FIRSTCONSTRUCTOR ******" << endl;
    CharLinkedList test_list;
    test_list.print();
    cout << "Expected outcome: " << "empty" << " and size is 0" << endl;
}

/* Tests single element constructor */
void secondConstructorTesting() {
    cout << "****** SECONDCONSTRUCTOR ******" << endl;
    CharLinkedList test_list('b');
    test_list.print();
    cout << "Expected outcome: " << "b" << " and size is 1" << endl;
}

/* Tests the array constructor */
void thirdConstructorTesting() {
    cout << "****** THIRDCONSTRUCTOR ******" << endl;
    char char_list[3] = {'a', 'b', 'c'};
    CharLinkedList test_list(char_list, 3);
    test_list.print();
    cout << "Expected outcome: " << "abc" << " and size is 3" << endl;
}

/* Tests the copy constructor */
void copyConstructorTesting() {
    cout << "****** COPYCONSTRUCTOR ******" << endl;
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    CharLinkedList copy_list(test_list);
    copy_list.print();
    cout << "Expected outcome: " << "lno" << " and size is 3" << endl;
}

/* Tests the assignment operator */
void assignmentOperatorTesting() {
    CharLinkedList test_list;
    CharLinkedList assignment_list;
    cout << "****** ASSIGNMENTOPERATOR ******" << endl;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    assignment_list = test_list;
    assignment_list.print();
    cout << "Expected outcome: " << "lno" << " and size is 3" << endl;
}

/* Tests the isEmpty function */
void isEmptyTesting() {
    CharLinkedList test_list;
    cout << "****** ISEMPTY ******" << endl;
    if(test_list.isEmpty()) {
        cout << "Checking if List is Empty" << endl;
    }
}

/* Tests the clear function */
void clearTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    cout << "****** CLEAR ******" << endl;
    test_list.clear();
    if(test_list.isEmpty()) {
        cout << "Checking if List is Clear" << endl;
    }
}

/* Tests the size function */
void sizeTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    cout << "****** SIZE ******" << endl;
    cout << "The size of the List is: " << test_list.size() << endl;
    cout << "Expected outcome: " << "3" << endl;
}

/* Tests the insertAt function */
void insertAtTesting() {
    CharLinkedList test_list;
    cout << "****** INSERT ******" << endl;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    test_list.insertAt(1, 'm');
    test_list.print();
    cout << "Expected outcome: " << "lmnopq" << " and size is 6" << endl;

    cout << "****** INSERT AT EXCEPTIONS ******" << endl;
    try {
        test_list.insertAt(-1, 'g');
    } catch (range_error) {
        cout << "index (" << "-1" << ") not in range [0.." <<
        test_list.size() << "]" << endl;
    }
}

/* Tests the insertInOrder function */
void insertInOrderTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** INSERTINORDER ******" << endl;
    test_list.insertInOrder('m');
    test_list.print();
    cout << "Expected outcome: " << "lmnopq" << " and size is 6" << endl;
}

/* Tests the first function */
void firstTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** FIRST ******" << endl;
    cout << "The first element of the list is: " << test_list.first() << endl;
    cout << "Expected outcome: " << "l" << endl;

    cout << "****** FIRST EXCEPTIONS ******" << endl;
    CharLinkedList exceptions;
    try {
        exceptions.first();
    } catch (const runtime_error& error) {
        cout << "cannot pop from empty doubly-linked list" << endl;
    }
}

/* Tests the last function */
void lastTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** LAST ******" << endl;
    cout << "The last element of the list is: " << test_list.last() << endl;
    cout << "Expected outcome: " << "q" << endl;

    cout << "****** LAST EXCEPTIONS ******" << endl;
    CharLinkedList exceptions;
    try {
        exceptions.last();
    } catch (const runtime_error& error) {
        cout << "cannot pop from empty doubly-linked list" << endl;
    }
}

/* Tests the pushAtBack function */
void pushAtBackTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** PUSHATBACK ******" << endl;
    test_list.pushAtBack('m');
    test_list.pushAtBack('s');
    test_list.print();
    cout << "Expected outcome: " << "lnopqms" << " and size is 7" << endl;
}

/* Tests the popFromBack function */
void popFromBackTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    test_list.pushAtBack('m');
    test_list.pushAtBack('s');
    cout << "****** POPFROMBACK ******" << endl;
    test_list.popFromBack();
    test_list.popFromBack();
    test_list.print();
    cout << "Expected outcome: " << "lnopq" << " and size is 5" << endl;

    cout << "****** POPFROMBACK EXCEPTIONS ******" << endl;
    CharLinkedList exceptions;
    try {
        exceptions.popFromBack();
    } catch (const runtime_error& error) {
        cout << "cannot pop from empty doubly-linked list" << endl;
    }
}

/* Tests the pushAtFront function */
void pushAtFrontTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** PUSHATFRONT ******" << endl;
    test_list.pushAtFront('m');
    test_list.pushAtFront('s');
    test_list.print();
    cout << "Expected outcome: " << "smlnopq" << " and size is 7" << endl;
}

/* Tests the popAtFront function */
void popFromFrontTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    test_list.pushAtFront('m');
    test_list.pushAtFront('s');
    cout << "****** POPFROMFRONT ******" << endl;
    test_list.popFromFront();
    test_list.popFromFront();
    test_list.print();
    cout << "Expected outcome: " << "lnopq" << " and size is 5" << endl;

    cout << "****** POPFROMFRONT EXCEPTIONS ******" << endl;
    CharLinkedList exceptions;
    try {
        exceptions.popFromFront();
    } catch (const runtime_error& error) {
        cout << "cannot pop from empty doubly-linked list" << endl;
    }
}

/* Tests the elementAt function */
void elementAtTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** ELEMENTAT ******" << endl;
    cout << "The third element in the list is: " << test_list.elementAt(2)
    << endl;
    cout << "Expected outcome: " << "o" << endl;

    cout << "****** ELEMENT AT EXCEPTIONS ******" << endl;
    try {
        test_list.elementAt(-1);
    } catch (range_error) {
        cout << "index (" << "-1" << ") not in range [0.." <<
        test_list.size() << "]" << endl;
    }
}

/* Tests the removeAt function */
void removeAtTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** REMOVE ******" << endl;
    test_list.removeAt(2);
    test_list.print();
    cout << "Expected outcome: " << "lnpq" << " and size is 4" << endl;

    cout << "****** REMOVE AT EXCEPTIONS ******" << endl;
    try {
        test_list.removeAt(-1);
    } catch (range_error) {
        cout << "index (" << "-1" << ") not in range [0.." <<
        test_list.size() << "]" << endl;
    }
}

/* Tests the replaceAt function */
void replaceAtTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** REPLACE ******" << endl;
    test_list.replaceAt(2, 'm');
    test_list.print();
    cout << "Expected outcome: " << "lnmpq" << " and size is 5" << endl;

    cout << "****** REPLACE AT EXCEPTIONS ******" << endl;
    try {
        test_list.replaceAt(20, 'g');
    } catch (range_error) {
        cout << "index (" << "20" << ") not in range [0.." <<
        test_list.size() << "]" << endl;
    }
}

/* Tests the concatenate function */
void concatenateTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** CONCATENATE ******" << endl;
    CharLinkedList new_list;
    new_list.insertAt(0, ' ');
    new_list.insertAt(1, 'r');
    new_list.insertAt(2, 's');
    new_list.insertAt(3, 't');
    test_list.concatenate(&new_list);
    test_list.print();
    cout << "Expected outcome: " << "lnopq rst" << " and size is 9" << endl;
}

/* Tests the find function */
void findTesting() {
    CharLinkedList test_list;
    test_list.insertAt(0, 'l');
    test_list.insertAt(1, 'n');
    test_list.insertAt(2, 'o');
    test_list.insertAt(3, 'p');
    test_list.insertAt(4, 'q');
    cout << "****** FIND ******" << endl;
    bool find = false;
    bool find2 = false;
    find = test_list.find('c');
    find2 = test_list.find('n');
    if(find == true) {
        cout << "Letter is found " << endl;
    } else {
        cout << "Letter is not found " << endl;
    }
    if(find2 == true) {
        cout << "Letter is found " << endl;
    } else {
        cout << "Letter is not found " << endl;
    }
    cout << "Expected outcome: " << "Letter is not found" << endl;
    cout << "Expected outcome: " << "Letter is found" << endl;
}
