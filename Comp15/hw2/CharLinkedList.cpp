/*
*
*  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
*
*  CharLinkedList.cpp
*  Complete CharLinkedList Class Implementation
*  Modified By (UTLN): Cheryl Melwani (cmelwa01)
*           On       : Feb 4th 2020
*
*/

#include <iostream>
#include "CharLinkedList.h"
#include <stdexcept>

using namespace std;

/* Function: nullary constructor
Parameters: none
Return Type: not applicable
Purpose: Nullary constructor that initializes the components of the
linked list to 0 and nullptr.
*/
CharLinkedList::CharLinkedList() {
    curr_pos = nullptr;
    front = nullptr;
    length = 0;
}

/* Function: single element constructor
Parameters: none
Return Type: not applicable
Purpose: initializes the components of the linked list to a single node
*/
CharLinkedList::CharLinkedList(char elem) {
    front = new Node;
    front->data = elem;
    front->previous = nullptr;
    front->next = nullptr;
    curr_pos = front;
    length = 1;
}

/* Function: array constructor
Parameters: none
Return Type: not applicable
Purpose: initializes the components of the linked list using elements
from a char list thats a parameter of the function.
*/

CharLinkedList::CharLinkedList(char char_list[], int size) {
    front = nullptr;
    length = 0;

    for(int i = 0; i < size; i++) {
        pushAtBack(char_list[i]);
    }
    length = size;
}
/* Purpose: Copy Constructor */
CharLinkedList::CharLinkedList(CharLinkedList &copy) {
    front = nullptr;
    curr_pos = nullptr;
    length = 0;
    for(int i = 0; i < copy.length; i++) {
        pushAtBack(copy.elementAt(i));
    }
}

CharLinkedList &CharLinkedList::operator= (const CharLinkedList &rhs) {
    clear();
    curr_pos = front;
    length = rhs.length;
    curr_pos = nullptr;

    if(rhs.front == nullptr) {
        front = nullptr;
    } else {
        front = new Node;
        front->data = rhs.front->data;
        Node *node = front;
        Node *original = rhs.front;

        while(original->next != nullptr) {
            node->next = new Node;
            node->next->data = original->next->data;
            original = original->next;
            node->next->previous = node;
            node = node->next;
        }
        node->next = nullptr;
    }
    return *this;
}

/* Purpose: Destructor */
CharLinkedList::~CharLinkedList() {
    curr_pos = front;
    Node *temp = front;
    while(curr_pos != nullptr) {
        temp = curr_pos->next;
        delete curr_pos;
        curr_pos = temp;
    }
    length = 0;
}

/* Function: isEmpty
Parameters: none
Return Type: boolean
Purpose: To check if the linked list is actually clear you call isEmpty
*/
bool CharLinkedList::isEmpty() {
    return length == 0;
}

/* Function: clear
Parameters: none
Return Type: void
Purpose: To clear the nodes in the linked list and set them all to nullptr.
*/
void CharLinkedList::clear() {
    curr_pos = front;
    Node *temp = front;
    while(curr_pos != nullptr) {
        temp = curr_pos->next;
        curr_pos->next = nullptr;
        curr_pos->previous = nullptr;
        curr_pos = nullptr;
        curr_pos = temp;
    }
    length = 0;
}

/* Function: size
Parameters: none
Return Type: int
Purpose: To be able to access the length since its a private variable
*/
int CharLinkedList::size() {
    return length;
}

/* Function: first
Parameters: none
Return Type: char
Purpose: Returns the first node in the linked list.
*/
char CharLinkedList::first() {
    if(isEmpty() == true) {
        throw runtime_error ("cannot get first of empty doubly-linked list");
    }
    return front->data;
}

/* Function: last
Parameters: none
Return Type: char
Purpose: Returns the last node in the linked list
*/
char CharLinkedList::last() {
    if(isEmpty() == true) {
        throw runtime_error ("cannot get last of empty doubly-linked list");
    }
    curr_pos = front;
    while(curr_pos->next != nullptr) {
        curr_pos = curr_pos->next;
    }
    return curr_pos->data;
}

/* Function:: elementAt
Parameters: index which is an integer
Return Type: char
Purpose: The user inputs an index and the function finds the node at the
given index. The function returns the data of that node.
*/
char CharLinkedList::elementAt(int index) {
    if (index < 0 || index >= size()) {
        throw range_error (" index (" + to_string(index) + ") not in range [0.."
        + to_string(size()) + "]");
    }
    curr_pos = front;
    for(int i = 0; i < index; i++) {
        curr_pos = curr_pos->next;
    }
    return curr_pos->data;
}

/* Function: insertAt
Parameters: a character called elem that the user inputs to insert into an
index. An integer called index that represents where elem will go in the
linked list.
Return Type: void
Purpose: This function's purpose is to insert a character into a specific
node in the linked list.
*/
void CharLinkedList::insertAt(int index, char elem) {
    if (index < 0 || index > size()) {
        throw range_error (" index (" + to_string(index) + ") not in range [0.."
        + to_string(size()) + "]");
    }
    if(index == 0) {
        pushAtFront(elem);
    } else if (index == length) {
        pushAtBack(elem);
    } else {
        curr_pos = front;
        for(int i = 0; i < index; i++) {
            curr_pos = curr_pos->next;
        }
        Node *new_node = new Node;
        Node *temp;
        new_node->next = curr_pos;
        new_node->previous = curr_pos->previous;
        new_node->data = elem;
        temp = curr_pos->previous;
        temp->next = new_node;
        curr_pos->previous = new_node;
        length++;
    }
}

/* Function: print
Parameters: none
Return Type: void
Purpose: The print functions prints out the char linked list along with its
length.
*/
void CharLinkedList::print() {
    curr_pos = front;

    cout << "[CharLinkedList of size " << size() << " <<";
    while(curr_pos != nullptr) {
        cout << curr_pos->data;
        curr_pos = curr_pos->next;
    }
    cout << ">>]" << endl;
}
/* Function: pushAtBack
Parameters: a character called elem that the user inputs to insert into the
back of the linked list.
Return Type: void
Purpose: The pushAtBack function takes in a character, and adds the character
to the back of the linked list.
*/
void CharLinkedList::pushAtBack(char elem) {
    Node *new_node = new Node;
    new_node->data = elem;
    new_node->next = nullptr;
    if(isEmpty()) {
        new_node->previous = nullptr;
        front = new_node;
    } else {
        curr_pos = front;
        while(curr_pos->next != nullptr) {
            curr_pos = curr_pos->next;
        }
        curr_pos->next = new_node;
        new_node->previous = curr_pos;
    }
    length++;
}

/* Function: pushAtFront
Parameters: a character called elem that the user inputs to insert into the
front of the linked list.
Return Type: void
Purpose: The pushAtFront function takes in a character, and adds the character
to the front of the linked list.
*/
void CharLinkedList::pushAtFront(char elem) {
    Node *new_node = new Node;
    if(isEmpty()) {
        new_node->previous = nullptr;
        new_node->next = nullptr;
        new_node->data = elem;
        front = new_node;
    } else {
        new_node->data = elem;
        new_node->next = front;
        new_node->previous = nullptr;
        front = new_node;
    }
    length++;
}

/* Function: insertInOrder
Parameters: a character called elem that the user inputs to insert into the
linked list.
Return Type: void
Purpose: This function takes in a element to insert into the linked list
alphabetically.
*/
void CharLinkedList::insertInOrder(char elem) {
    bool check = false;
    int index, count = 0;
    curr_pos = front;
    while((curr_pos != nullptr) && (check == false)) {
        if(elem < curr_pos->data) {
            check = true;
            index = count;
        }
        count++;
        curr_pos = curr_pos->next;
    }
    if(check == false) {
        index = length;
    }
    insertAt(index, elem);
}

/* Function: popFromFront
Parameters: none
Return Type: void
Purpose: This function's purpose is to remove an element from the front of the
linked list.
*/
void CharLinkedList::popFromFront() {
    Node *to_delete = front;
    if(isEmpty() == true) {
        throw runtime_error ("cannot pop from empty doubly-linked list");
    }
    if(length == 1) {
        front = nullptr;
        delete to_delete;
    } else {
        to_delete->next->previous = nullptr;
        front = to_delete->next;
        delete to_delete;
    }
    length--;
}

/* Function: popFromFront
Parameters: none
Return Type: void
Purpose: This function's purpose is to remove an element/node from the back of
the linked list.
*/
void CharLinkedList::popFromBack() {
    Node *to_delete = front;
    if(isEmpty() == true) {
        throw runtime_error ("cannot pop from empty doubly-linked list");
    }
    if(length == 1) {
        front = nullptr;
        delete to_delete;
    } else {
        curr_pos = front;
        while(curr_pos->next != nullptr) {
            curr_pos = curr_pos->next;
        }
        to_delete = curr_pos;
        to_delete->previous->next = nullptr;
        curr_pos = to_delete->previous;
        delete to_delete;
    }
    length--;
}

/* Function: removeAt
Parameters: an integer called index that specifies the specific location that
that the element should be removed from.
Return Type: void
Purpose: This function's purpose is to remove a node at a specific index
in the linked list.
*/
void CharLinkedList::removeAt(int index) {
    if (index < 0 || index > size()) {
        throw range_error (" index (" + to_string(index) + ") not in range [0.."
        + to_string(size()) + "]");
    }
    if(index == 0) {
        popFromFront();
    } else if (index == length) {
        popFromBack();
    } else {
        curr_pos = front;
        for(int i = 0; i < index; i++) {
            curr_pos = curr_pos->next;
        }
        curr_pos->previous->next = curr_pos->next;
        curr_pos->next->previous = curr_pos->previous;
        length--;
    }
}

/* Function: replaceAt
Parameters: an integer called index that specifies the location that
that the element should be removed from and a character called elem that
is being put into the linked list.
Return Type: void
Purpose: This function's purpose is to replace an element at a specific index
in the linked list.
*/
void CharLinkedList::replaceAt(int index, char elem) {
    if (index < 0 || index > size()) {
        throw range_error (" index (" + to_string(index) + ") not in range [0.."
        + to_string(size()) + "]");
    }
    curr_pos = front;
    for(int i = 0; i < index; i++) {
        curr_pos = curr_pos->next;
    }
    curr_pos->data = elem;
}

/* Function: concatenate
Parameters: a CharLinkedList called new_list
Return Type: void
Purpose: The purpose of this function is to combine two char linked lists
together.
*/
void CharLinkedList::concatenate(CharLinkedList *new_list) {
    int new_size = new_list->size();
    for(int i = 0; i < new_size; i++) {
        pushAtBack(new_list->elementAt(i));
    }
}

/* Function: find
Parameters: A character called elem
Return Type: bool
Purpose: The purpose of this function is to find a character that the user
inputs inside the linked list. Returns true if the char is found, and
returns false if it isn't.
*/
bool CharLinkedList::find(char elem) {
    curr_pos = front;
    return findHelper(curr_pos, elem);
}

/* Function: findHelper
Parameters: Node pointer called curr_node and a character called elem
Return Type: bool
Purpose: This function is a helper function for the find function. This
function actually recursively finds whether the character the user inputs
is found in the linked list or not. It recursively traverses through the
linked list.
*/
bool CharLinkedList::findHelper(Node *curr_node, char elem) {
    if(curr_node == nullptr) {
        return false;
    }
    if(curr_node->data == elem) {
        return true;
    } else {
        return findHelper(curr_node->next, elem);
    }
}
