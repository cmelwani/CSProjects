/*
 *      Stack.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      Implementation of the Stack class
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 */


#include <iostream>

#include "Stack.h"

using namespace std;

/*
 * Default constructor:  nothing necessary.
 * Data member constructor runs automatically.
 */
Stack::Stack() 
{
	// The sequence is automatically initialized
}

/*
 * If given an initial capacity, we need to run the non-default
 * constructor for our sequence data member.
 * In C++ this is one using  something called a "member initialization
 * list," which is a bunch of initializations specified after the
 * function head and a colon and before the opening brace of the
 * function body.
 */
Stack::Stack(int initialCapacity) : stack(initialCapacity)
{
	// Work done in member initialization list
}

Stack::~Stack() 
{
        // nothing to do:  sequence destructor runs automatically
}

/*
 * Remove top element from the stack and return it.
 */
ElementType Stack::pop()
{
        // TODO
}

/*
 * Add given element to the top of the stack.
 */
void Stack::push(ElementType element) 
{
        // TODO
}

/*
 * Print contents in stack in order from top to bottom
 */
void Stack::printStack() 
{
        stack.printBuffer();
}
