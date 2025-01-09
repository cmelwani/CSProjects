/*
 * LinkedList.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation for Linked List of Planets
 *
 * What is an astronaut's favorite candy bar?
 *
 * A mars bar!
 */

#include <ostream>

#include "LinkedList.h"

using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
}

// Assignment operator
LinkedList &LinkedList::operator= (const LinkedList &rhs)
{
    length   = rhs.length;
    curr_pos = nullptr;

    if (rhs.front == nullptr) {
        front = nullptr;
    } else {
        front = new Node;
        front->info = rhs.front->info;
        Node *curr = front;
        Node *orig = rhs.front;

        while (orig->next != nullptr) {
            curr->next = new Node;
            curr->next->info = orig->next->info;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function insert_planet
// Input: Planet object
// Returns: None
// Does: Adds Planet to beginning of array, increases length
void LinkedList::insert_planet(Planet p)
{
    Node *node = new Node;

    node->info = p;
    node->next = front;

    front = node;
    length++;
}


// Function insert_planet_at_back
// Input: Planet object
// Returns: None
// Does: Adds Planet to end of array, increases length
void LinkedList::insert_planet_at_back(Planet p)
{
  Node *node = new Node;
  node->info = p;
  node->next = nullptr;

  if(front == nullptr) {
    front = node;
  }
  else {
    Node *temp = front;
    while(temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = node;
    length++;
  }
// TODO:  YOUR CODE HERE
// This function should insert the given planet at he back of the list
}

// Function get_next_planet
// Inputs: none
// Returns: none
// Does: Returns the Planet object at the current pos
//       Wraps around to beginning if we're at the end
//       Returns a default planet if empty
Planet LinkedList::get_next_planet()
{
    if (length == 0) {
        Planet p;
        return p;
    }
    if (curr_pos == nullptr)
        curr_pos = front;
    else
        curr_pos = curr_pos->next;
    return curr_pos->info;
}

// Function get_length, const
// Inputs: none
// Returns: int, length of list
int LinkedList::get_length() const
{
    return length;
}

// Function print, const
// Inputs: ostream object
// Returns: none
// Does: prints every element in the list
void LinkedList::print(ostream &out) const
{
    Node *node = front;

    while (node != nullptr) {
        (node->info).print(out);
        out << endl;
        node = node->next;
    }
}
