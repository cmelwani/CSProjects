/*
 *      Stack.h 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      A class that represents a stack of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation and include guards
 *      2020-01-31 Modified by Juliana vega
 *                 Removed "sequence" wording
 */
#ifndef STACK_H
#define STACK_H

#include "ElementType.h"
#include "CircularBuffer.h"

class Stack 
{
public:
        Stack();
        Stack(int capacity);
        ~Stack();

        ElementType pop();
        void        push(ElementType element);

        void        printStack();

private:
        CircularBuffer stack;
};

#endif
