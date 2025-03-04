/*
 *                      bit2.c
 *
 *         This file provides the implementation of the Bit2 data
 *         structure. Bit2 is a two dimensional Bit Vector. 
 *         
 *         Author: Cheryl Melwani (cmelwa01) and Anna Wang (awang15)
 *         Date: February 21st 2021
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "bit2.h"
#include "bit.h"
#include "assert.h"
#include "mem.h"

#define T Bit2_T

struct Bit2_T {
    int width;
    int height;
    Bit_T bitArr;
};

/* Creates a new 2D Bit Vector */
extern T Bit2_new  (int width, int height) {
    assert((width > 0 && height > 0) || 
            (width == 0 && height == 0));

    T bitArr2;
    NEW(bitArr2);
    int length = width * height;

    bitArr2->width = width;
    bitArr2->height = height;
    bitArr2->bitArr = Bit_new(length);

    return bitArr2;
}

/* Handles freeing the 2D Bit Vector created*/
extern void Bit2_free  (T *Bit2) {
    assert(Bit2 != NULL);
    assert(*Bit2 != NULL);
    Bit_free(&((*Bit2)->bitArr));
    FREE(*Bit2);
}

/* Returns the width of the 2D Bit Vector */
extern int Bit2_width  (T Bit2) {
    assert(Bit2 != NULL);
    return Bit2->width;
}

/* Returns the height of the 2D Bit Vector */
extern int Bit2_height  (T Bit2) {
    assert(Bit2 != NULL);
    return Bit2->height;
}

/* Returns the element in 2D Bit Vector at (column, row) */
extern int Bit2_get  (T Bit2, int column, int row) {
    assert(column >= 0 && column < Bit2->width);
    assert(row >= 0 && row < Bit2->height);
    assert(Bit2 != NULL);

    return Bit_get(Bit2->bitArr, (((Bit2->width) * row) + column)); 
}

/* Populates the element at (column, row) with bit and 
   returns the previous element in (column, row) */
extern int Bit2_put  (T Bit2, int column, int row, int bit) {
    assert(column >= 0 && column < Bit2->width);
    assert(row >= 0 && row < Bit2->height);
    assert(Bit2 != NULL);
    assert(bit == 1 || bit == 0);

    return Bit_put(Bit2->bitArr, (((Bit2->width) * row) + column), bit);
}  

/* Calls the apply function for all elements in the 2D Bit Vector 
according to row major */
extern void Bit2_map_row_major  (T Bit2, void apply(int i, int j, 
    Bit2_T a, int b, void *p1), void *cl) {
    
    assert(Bit2 != NULL);
    assert(Bit2->bitArr != NULL);
    assert(apply != NULL);

    for(int j = 0; j < (Bit2->height); j++) {
        for(int i = 0; i < (Bit2->width); i++) {
            apply(i, j, Bit2, Bit2_get(Bit2, i, j), cl);
        }
    }
}

/* Calls the apply function for all elements in the 2D Bit Vector 
according to row major */
extern void Bit2_map_col_major  (T Bit2, void apply(int i, int j, 
    Bit2_T a, int b, void *p1), void *cl) {

    assert(Bit2 != NULL);
    assert(Bit2->bitArr != NULL);
    assert(apply != NULL);

    for(int i = 0; i < (Bit2->width); i++) {
        for(int j = 0; j < (Bit2->height); j++) {
            apply(i, j, Bit2, Bit2_get(Bit2, i, j), cl);
        }
    }
}