/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  CharArrayList.cpp
 *
 *  Complete CharArrayList Class Implementation
 *
 *  Modified By YOUR NAME: CHERYL MELWANI
 *           On          : 28TH OF JANUARY 2020
 *
 */

//test constructors
 // tabing and layout for comp15
 // README

#include <iostream>
#include "CharArrayList.h"

using namespace std;

/* Function: nullary constructor
Parameters: none
Return Type: not applicable
Purpose: Nullary constructor that initializes the components of an
arraylist to 0.
*/
CharArrayList::CharArrayList() {
  num_chars = 0;
  capacity = 0;
  arr = new char[capacity];
 }

 /* Function: single element constructor
 Parameters: none
 Return Type: not applicable
 Purpose: initializes the components of the arraylist to a single element
 */
CharArrayList::CharArrayList(char elem) {
   arr = new char[1];
   arr[0] = elem;
   num_chars = 1;
   capacity = 1;
 }

 /* Function: constructor
 Parameters: none
 Return Type: not applicable
 Purpose: initializes the components of the arraylist.
 */
CharArrayList::CharArrayList(char *read_arr, int size) {
   arr = new char[size];
   for(int i = 0; i < size; i++) {
     arr[i] = read_arr[i];
   }
   num_chars = size;
   capacity = size;
 }

 /* Purpose: Copy Constructor */
CharArrayList::CharArrayList(CharArrayList &copy) {
  capacity = copy.getCapacity();
  num_chars = copy.size();
  arr = new char[capacity];
  for(int i = 0; i < num_chars; i++) {
    arr[i] = copy.elementAt(i);
  }
}

/* Purpose: Assignment Operater */
CharArrayList &CharArrayList::operator= (CharArrayList &rhs) {
  if(this != &rhs) {
    cerr << "Assignment recycling: " << num_chars << endl;
    delete [] arr;
    num_chars = rhs.size();
    arr = new char[num_chars];
    cerr << "Assignment allocated: " << num_chars << endl;
    for(int i = 0; i < num_chars; i++) {
      arr[i] = rhs.elementAt(i);
    }
  }
  return *this;
}


/* Purpose: Destructor */
CharArrayList::~CharArrayList() {
 	delete [] arr;
 	arr = NULL;
 }

 /* Function: isEmpty
 Parameters: none
 Return Type: boolean
 Purpose: To check if the array is actually clear you call isEmpty
 */
bool CharArrayList::isEmpty() {
   return num_chars == 0;
 }

 /* Function: clear
 Parameters: none
 Return Type: void
 Purpose: To clear the num_chars(size) and capacity of the arraylist
 */
void CharArrayList::clear() {
   num_chars = 0;
   capacity = 0;
 }

 /* Function: size
 Parameters: none
 Return Type: int
 Purpose: To be able to access the size since its a private variable
 */
int CharArrayList::size() {
  return num_chars;
}

/* Function: getCapacity
Parameters: none
Return Type: int
Purpose: To be able to access the capacity since its a private variable
*/
int CharArrayList::getCapacity() {
  return capacity;
}

/* Function: first
Parameters: none
Return Type: char
Purpose: Returns the first element in the array list
*/
char CharArrayList::first() {
  if(isEmpty() == true) {
    throw range_error ("cannot get first of empty ArrayList");
  }
  return arr[0];
}

/* Function: last
Parameters: none
Return Type: char
Purpose: Returns the last element in the array list
*/
char CharArrayList::last() {
  if(isEmpty() == true) {
    throw range_error ("cannot get first of empty ArrayList");
  }
  return arr[num_chars - 1];
}

/* Function:: elementAt
Parameters: index which is an integer
Return Type: char
Purpose: The user inputs an index and the function finds the element at the
given index.
*/
char CharArrayList::elementAt(int index) {
  if (index < 0 || index >= num_chars) {
    throw range_error (" index (" + to_string(index) + ") not in range [0.."
    + to_string(num_chars) + "]");
  }
  return arr[index];
}

/* Function: print
Parameters: none
Return Type: void
Purpose: The print functions prints out the char array list along with its
size.
*/
void CharArrayList::print() {
  cout << "[CharArrayList of size " << num_chars << " <<";
  for (int i = 0; i < size(); i++) {
    cout << elementAt(i);
  }
  cout << ">>]" << endl;
}

/* Function: expand
Parameters: none
Return Type: void
Purpose: The expand function doubles the capacity of the array list unless the
array list has a capacity of 0. If that's the case, then the capacity is added
by 1. The expand function calls the resize function to copy the elements of
the original array to the longer new array list.
*/
void CharArrayList::expand() {
  if(capacity == 0) {
    capacity += 1;
  } else {
    capacity *= 2;
  }
	resize(capacity);
}

/* Function: shrink
Parameters: none
Return Type: void
Purpose: The shrink function calls the resize function to resize the array list
to the size of num_chars and to copy the elements from the old array to the
new shorter array.
*/
void CharArrayList::shrink() {
	resize(num_chars);
}

/* Function: resize
Parameters: an integer called new_size that represents the size the array List
should be changed to.
Return Type: void
Purpose: The resize function takes in a size, creates a new char array list
with this size and then copies all the elements from the old array list to the
new array list.
*/
void CharArrayList::resize(int new_size) {
	char *new_arr = new char[new_size];
	//copy info from old array to new array
	for(int i = 0; i < num_chars; i++) {
		new_arr[i] = arr[i];
	}
	//delete old array
	delete [] arr;
	//repoint the pointer
	arr = new_arr;
	new_arr = NULL;
	//update the capacity
	capacity = new_size;
}

/* Function: pushAtBack
Parameters: a character called elem that the user inputs to insert into the
back of the array list.
Return Type: void
Purpose: The pushAtBack function takes in a character, and adds the character
to the back of the array. If the number of characters is equal to the capacity
then the function will call the expand function to expand the capacity of the
array.
*/
void CharArrayList::pushAtBack(char elem) {
  if(num_chars == capacity) {
		expand();
	}
	arr[num_chars] = elem;
	num_chars++;
}

/* Function: pushAtFront
Parameters: a character called elem that the user inputs to insert into the
front of the array list.
Return Type: void
Purpose: The pushAtFront function takes in a character, and adds the character
to the front of the array. If the number of characters is equal to the capacity
then the function will call the expand function to expand the capacity of the
array.
*/
void CharArrayList::pushAtFront(char elem) {
  if(num_chars == capacity) {
    expand();
  }
  for(int i = num_chars-1; i >= 0; i--) {
    arr[i+1] = arr[i]; //shifting right
  }
  arr[0] = elem;
  num_chars++;
}

/* Function: insertAt
Parameters: a character called elem that the user inputs to insert into an
index. An integer called index that represents where elem will go in the
array list.
Return Type: void
Purpose: This function's purpose is to insert an element into a specific index.
*/
void CharArrayList::insertAt(int index, char elem) {
  if (index < 0 || index > num_chars) {
    throw range_error (" index (" + to_string(index) + ") not in range [0.."
    + to_string(num_chars) + ")");
  }
  if(num_chars == capacity) {
    expand();
  }
  for(int i = num_chars-1; i >= index; i--) {
    arr[i+1] = arr[i];
  }
  arr[index] = elem;
  num_chars++;
}

/* Function: insertInOrder
Parameters: a character called elem that the user inputs to insert into an
array list.
Return Type: void
Purpose: This function takes in a element to insert into the array list
alphabetically.
*/
void CharArrayList::insertInOrder(char elem) {
  for(int i = 0; i < num_chars; i++) {
    if((elem > arr[i]) && (elem <= arr[i+1])) {
      insertAt(i+1, elem);
    }
  }
}

/* Function: popFromFront
Parameters: none
Return Type: void
Purpose: This function's purpose is to remove an element from the front of the
array list and shift all the elements to the left.
*/
void CharArrayList::popFromFront() {
  if(isEmpty() == true) {
    throw range_error ("cannot pop from empty ArrayList");
  }
  for(int i = 1; i < num_chars; i++) {
    arr[i-1] = arr[i];
  }
  num_chars--;
  shrink();
}

/* Function: popFromBack
Parameters: none
Return Type: void
Purpose: This function's purpose is to remove an element from the back of the
array list.
*/
void CharArrayList::popFromBack() {
  if(isEmpty() == true) {
    throw range_error ("cannot pop from empty ArrayList");
  }
  num_chars--;
  shrink();
}

/* Function: removeAt
Parameters: an integer called index that specifies the specific location that
that the element should be removed from.
Return Type: void
Purpose: This function's purpose is to remove an element at a specific index.
*/
void CharArrayList::removeAt(int index) {
  if (index < 0 || index >= num_chars) {
    throw range_error (" index (" + to_string(index) + ") not in range [0.."
    + to_string(num_chars) + "]");
  }
  for(int i = index+1; i < num_chars; i++) {
    arr[i-1] = arr[i];
  }
  num_chars--;
  shrink();
}

/* Function: replaceAt
Parameters: an integer called index that specifies the specific location that
that the element should be removed from and a character called elem that
is being put into the array list.
Return Type: void
Purpose: This function's purpose is to replace an element at a specific index.
*/
void CharArrayList::replaceAt(int index, char elem) {
  if (index < 0 || index >= num_chars) {
    throw range_error (" index (" + to_string(index) + ") not in range [0.."
    + to_string(num_chars) + "]");
  }
  arr[index] = elem;
}

/* Function: concatenate
Parameters: a CharArrayList called new_arr
Return Type: void
Purpose: The purpose of this function is to combine two char array lists
together.
*/
void CharArrayList::concatenate(CharArrayList *new_arr) {
  for(int i = 0; i < new_arr->size(); i++) {
    pushAtBack(new_arr->elementAt(i));
  }
}
