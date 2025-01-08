/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  CharArrayList.h
 *
 *  Complete Array List Class Declaration
 *
 *  Modified By YOURNAME: Cheryl Melwani
 *           On         :
 *
 */

#include <string>

#ifndef CHARARRAYLIST_H
#define CHARARRAYLIST_H

using namespace std;

class CharArrayList {
public:
  CharArrayList();
  CharArrayList(char elem);
  CharArrayList(char *read_arr, int size);
  CharArrayList(CharArrayList &copy);
  CharArrayList &operator= (CharArrayList &rhs);
  ~CharArrayList();

  bool isEmpty(); //empty()
  void clear();
  int size(); // size()
  char first(); // front()
  char last(); // back()
  char elementAt(int index); // at(int index)
  void print();

  void pushAtBack(char elem); //push_back()
  void pushAtFront(char elem);
  void insertAt(int index, char elem); //insert()
  void insertInOrder(char elem);
  void popFromFront();
  void popFromBack(); //pop_back()
  void removeAt(int index); //erase()
  void replaceAt(int index, char elem);
  void concatenate(CharArrayList *new_arr);
  void shrink();

private:
  char *arr;
  int num_chars;
  int capacity;

//helper functions
  void shift();
  void expand();
  void resize(int new_size);
  int getCapacity();

};

#endif
