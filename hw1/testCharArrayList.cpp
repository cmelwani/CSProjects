/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  testCharArrayList.cpp
 *  Testing File for the sequence CharArrayList class
 *
 *  Written by: Cheryl Melwani
 *        UTLN:
 *          on: 28th January 2020
 */

#include <iostream>
#include "CharArrayList.h"

using namespace std;

//void firstConstructorTesting();
//void secondConstructorTesting();
//void thirdConstructorTesting();
void isEmptyTesting();
void clearTesting();
void sizeTesting();
void insertAtTesting(); //elementAt and print testing as well
void firstTesting();
void lastTesting();
void elementAtTesting();
void insertInOrderTesting();
void pushAtBackTesting();
void pushAtFrontTesting();
void popFromFrontTesting();
void popFromBackTesting();
void removeAtTesting();
void replaceAtTesting();
void concatenateTesting();

CharArrayList test_array;

int main() {
  //firstConstructorTesting();
  //secondConstructorTesting();
  //thirdConstructorTesting();
  isEmptyTesting();
  clearTesting();
  sizeTesting();
  insertAtTesting();
  firstTesting();
  lastTesting();
  elementAtTesting();
  insertInOrderTesting();
  pushAtBackTesting();
  pushAtFrontTesting();
  popFromFrontTesting();
  popFromBackTesting();
  removeAtTesting();
  replaceAtTesting();
  concatenateTesting();
}

/*
void firstConstructorTesting() {
  cout << "Nullary constructor sets size to " << test_array.size()
  << " and capacity to " << test_array.getCapacity() << endl;
}

void secondConstructorTesting() {
  cout << "Single element constructor sets size to " << test_array.size() <<
  " and capacity to " << test_array.getCapacity() << endl;
  test_array.print();
}

void thirdConstructorTesting() {
  cout << "Single element constructor sets size to " << test_array.size() <<
  " and capacity to " << test_array.getCapacity() << endl;
  test_array.print();
}
*/

void isEmptyTesting() {
  cout << "****** ISEMPTY ******" << endl;
  if(test_array.isEmpty()) {
    cout << "Checking if Array is Empty" << endl;
  }
}

void clearTesting() {
  cout << "****** CLEAR ******" << endl;
  test_array.clear();
  if(test_array.isEmpty()) {
    cout << "Checking if Array is Clear" << endl;
  }
}

void sizeTesting() {
  cout << "****** SIZE ******" << endl;
  cout << "The size of the array is: " << test_array.size() << endl;
  cout << "Expected outcome: " << "0" << endl;
}

void insertAtTesting() {
  cout << "****** INSERT ******" << endl;
  test_array.insertAt(0, 'l');
  test_array.insertAt(1, 'n');
  test_array.insertAt(2, 'o');
  test_array.insertAt(3, 'p');
  test_array.insertAt(4, 'q');
  test_array.print();
  cout << "Expected outcome: " << "lnopq" << " and size is 5" << endl;
  //TESTING ERROR MESSAGES
  //test_array.insertAt(20, 'i'); - EXCEPTION EROSE AS EXPECRTED
  //test_array.insertAt(-1, 'k'); - EXCEPTION EROSE AS EXPECRTED
}

void firstTesting() {
  cout << "****** FIRST ******" << endl;
  cout << "The first element of the array is: " << test_array.first() << endl;
  cout << "Expected outcome: " << "l" << endl;
}

void lastTesting() {
  cout << "****** LAST ******" << endl;
  cout << "The last element of the array is: " << test_array.last() << endl;
  cout << "Expected outcome: " << "q" << endl;
}

void elementAtTesting() {
  cout << "****** ELEMENTAT ******" << endl;
  cout << "The third element in the array is: " << test_array.elementAt(3)
  << endl;
  cout << "Expected outcome: " << "p" << endl;
  //TESTING ERROR MESSAGES
  //test_array.elementAt(-1); - EXCEPTION EROSE AS EXPECRTED
  //test_array.elementAt(20); - EXCEPTION EROSE AS EXPECRTED
}

void insertInOrderTesting() {
  cout << "****** INSERTINORDER ******" << endl;
  test_array.insertInOrder('m');
  test_array.print();
  cout << "Expected outcome: " << "lmnopq" << " and size is 6" << endl;
}

void pushAtBackTesting() {
  cout << "****** PUSHATBACK ******" << endl;
  test_array.pushAtBack('m');
  test_array.print();
  cout << "Expected outcome: " << "lmnopqm" << " and size is 7" << endl;
}

void pushAtFrontTesting() {
  cout << "****** PUSHATFRONT ******" << endl;
  test_array.pushAtFront('s');
  test_array.print();
  cout << "Expected outcome: " << "slmnopqm" << " and size is 8" << endl;
}

void popFromFrontTesting() {
  cout << "****** POPFROMFRONT ******" << endl;
  test_array.popFromFront();
  test_array.print();
  cout << "Expected outcome: " << "lmnopqm" << " and size is 7" << endl;
}

void popFromBackTesting() {
  cout << "****** POPFROMBACK ******" << endl;
  test_array.popFromBack();
  test_array.print();
  cout << "Expected outcome: " << "lmnopq" << " and size is 6" << endl;
}

void removeAtTesting() {
  cout << "****** REMOVE ******" << endl;
  test_array.removeAt(3);
  test_array.print();
  cout << "Expected outcome: " << "lmnpq" << " and size is 5" << endl;
  //TESTING ERROR MESSAGES
  //test_array.removeAt(-1); - EXCEPTION EROSE AS EXPECRTED
  //test_array.removeAt(20); - EXCEPTION EROSE AS EXPECRTED
}

void replaceAtTesting() {
  cout << "****** REPLACE ******" << endl;
  test_array.replaceAt(2, 'a');
  test_array.print();
  cout << "Expected outcome: " << "lmapq" << " and size is 5" << endl;
  //TESTING ERROR MESSAGES
  //test_array.replaceAt(-1, 'k'); - EXCEPTION EROSE AS EXPECRTED
  //test_array.replaceAt(20, 'k'); - EXCEPTION EROSE AS EXPECRTED
}

void concatenateTesting() {
  cout << "****** CONCATENATE ******" << endl;
  CharArrayList new_array;
  new_array.insertAt(0, ' ');
  new_array.insertAt(1, 'r');
  new_array.insertAt(2, 's');
  new_array.insertAt(3, 't');
  test_array.concatenate(&new_array);
  test_array.print();
  cout << "Expected outcome: " << "lmapq rst" << " and size is 9" << endl;
}
