/*
 *      CircularBuffer.cpp
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 *      2019-08-01 Modified by Alice Dempsey
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 */

#include <iostream>
#include <stdexcept>

#include "CircularBuffer.h"


using namespace std;


/*
 * Return the index of the next element in the buffer.
 * Wraps around!
 */

int CircularBuffer::nextIndex(int index)
{
        // TODO
        index = (index + 1) % 6;
        return index;
}

int CircularBuffer::prevIndex(int index) {
  if(index == 0) {
    return currentSize-1;
  }
  index = (index - 1) % 6;
  return index;
}


/* Default Constructor */
CircularBuffer::CircularBuffer()
{
        init(INIT_CAPACITY);
}

/*
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity.
 */
CircularBuffer::CircularBuffer(int initialCapacity)
{
        init(initialCapacity);
}

/*
 * Initialize a new, empty CircularBuffer with an initial capacity.
 */
void CircularBuffer::init(int initialCapacity)
{
        capacity      = initialCapacity;
        bufferArray = new ElementType[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularBuffer::~CircularBuffer()
{
        delete [] bufferArray;
}

/*
 *  Add given element to the back of the list
 */
void CircularBuffer::addAtBack(ElementType elem)
{
        if (currentSize == capacity) {
                expand();
        }
        bufferArray[back] = elem;
        currentSize++;
        back                = nextIndex(back);
}

/*
 *  Add given element to the front of the list
 */
void CircularBuffer::addAtFront(ElementType elem)
{
        if(currentSize == capacity) {
          expand();
        }
        bufferArray[front] = elem;
        currentSize++;
        front = prevIndex(front);
}

/*
 * Remove the element at the back of the list
 * and return it.
 */
ElementType CircularBuffer::removeFromBack()
{
    if(currentSize == 0)
        return NULL;

    back = back - 1;
    if(back < 0)
        back = capacity - front - 1;

    currentSize --;

    return bufferArray[back];
}

/*
 * Remove the element at the front of the list
 * and return it.
 */

ElementType CircularBuffer::removeFromFront()
{
         // TODO
         if(currentSize == 0) {
           return NULL;
         }
         int nextIndex = prevIndex(front);
         front = nextIndex;
         currentSize --;

         return bufferArray[front];
}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularBuffer::expand()
{
        // TODO
        ElementType *new_array = new ElementType[capacity * 2];

        for(int i = 0; i < capacity; i++) {
          new_array[i] = bufferArray[i];
        }
        
        front = 0;
        back = currentSize--;
        delete [] bufferArray;
        bufferArray = new_array;
        capacity = capacity * 2;
}

/*
 * Print the contents of the CircularBuffer, one element per line.
 */
void CircularBuffer::printBuffer()
{
        int currIndex = front;
        for (int i = 0; i < currentSize; i++) {
                cout << bufferArray[currIndex] << endl;
                currIndex = nextIndex(currIndex);
        }
}
