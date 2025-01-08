
/*
*
*  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
*
*  CharLinkedList.cpp
*  Complete CharLinkedList Class Header and Declaration
*  Modified By (UTLN): Cheryl Melwani (cmelwa01)
*           On       : Feb 4th 2020
*
*/

#include <string>
#include <stdexcept>

#ifndef CHARLINKEDLIST_H
#define CHARLINKEDLIST_H

class CharLinkedList {
public:
    CharLinkedList();
    CharLinkedList(char elem);
    CharLinkedList(CharLinkedList &copy);
    CharLinkedList(char char_list[], int size);
    CharLinkedList &operator=(const CharLinkedList &rhs);
    ~CharLinkedList();

    bool isEmpty();
    void clear();
    int size();
    char first();
    char last();
    char elementAt(int index);
    void print();

    void pushAtBack(char elem);
    void pushAtFront(char elem);
    void insertAt(int index, char elem);
    void insertInOrder(char elem);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(int index, char elem);
    void concatenate(CharLinkedList *new_list);
    void shrink(); //linked list doesn't need a shrink function
    bool find(char elem);

private:
    int length;
    struct Node {
        char data;
        Node *previous;
        Node *next;
    };
    Node *front;
    Node *curr_pos;

    //helper functions
    void shift();
    void expand();
    void resize(int new_size);
    bool findHelper(Node *curr_pos, char elem);

};

#endif
