/*
 *      Queue.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 */

#include <iostream>
#include "Queue.h"

using namespace std;


/*
 * Default constructor:  nothing necessary.
 * Data member constructor runs automatically.
 */
Queue::Queue() 
{
        // circular Buffer initialized automatically
}

/*
 * If given an initial capacity, we need to run the non-default
 * constructor for our sequence data member.
 * In C++ this is one using  something called a "member initialization
 * list," which is a bunch of initializations specified after the
 * function head and a colon and before the opening brace of the
 * function body.
 */
Queue::Queue(int initialCapacity) : queue(initialCapacity)
{
        // done in member initialization list
}

Queue::~Queue() 
{
        // nothing to do:  Buffer destructor runs automatically
}

/*
 * Remove the first element in the queue and return it.
 */
ElementType Queue::dequeue() 
{
        // TODO
}

/*
 * Add a new element to the back of the queue.
 */
void Queue::enqueue(ElementType element) 
{
        // TODO
}

/*
 * Print the contents of the queue in order.
 */
void Queue::printQueue() 
{
        queue.printBuffer();
}
