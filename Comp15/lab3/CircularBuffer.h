/*
 *      CircularBuffer.h
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon, Tufts University
 *                 Added documentation and nextIndex() function.
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 */


#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "ElementType.h"

class CircularBuffer
{
public:
        CircularBuffer();
        CircularBuffer(int givenCapcity);
        ~CircularBuffer();

        void        addAtBack (ElementType elem);
        void        addAtFront(ElementType elem);
        ElementType removeFromBack();
        ElementType removeFromFront();

        void        printBuffer();

private:
        static const int INIT_CAPACITY = 5;

        ElementType     *bufferArray;
        int              currentSize;
        int              capacity;
        int              front;
        int              back;

        int  nextIndex(int index);
        int  prevIndex(int index);
        void expand();
        void init(int givenCapacity);
};

#endif
