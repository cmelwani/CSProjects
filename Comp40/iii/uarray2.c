/*
 *                      uarray2.c
 *
 *         This file provides the implementation of the UArray2 data
 *         structure. UArray2 is a two dimensional UArray. 
 *         
 *         Author: Cheryl Melwani (cmelwa01) and Anna Wang (awang15)
 *         Date: February 21st 2021
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "uarray.h"
#include "uarray2.h"
#include "assert.h"
#include "mem.h"

#define T UArray2_T

struct UArray2_T {
    int width;
    int height;
    int size;
    UArray_T uarray;
};

/* Creates a new 2D UArray */
extern T UArray2_new (int width, int height, int size) {
    assert(size > 0);
    assert((width > 0 && height > 0) || 
            (width == 0 && height == 0));
    
    int length = width * height;
    T uarray2;
    NEW(uarray2);
    
    uarray2->uarray = UArray_new(length, size);
    uarray2->width = width;
    uarray2->height = height;
    uarray2->size = size;
    return uarray2;
}

/* Handles freeing the 2D UArray created*/
extern void UArray2_free (T *uarray2) {
    assert(uarray2 != NULL);
    assert(*uarray2 != NULL); 
    
    UArray_free(&((*uarray2)->uarray));
    FREE(*uarray2);
}

/* Returns the size of the elements in the 2D UArray */
extern int UArray2_size (T uarray2) {    
    assert(uarray2 != NULL);
    return uarray2->size;
}

/* Returns the width of the 2D UArray */
extern int UArray2_width (T uarray2) {
    assert(uarray2 != NULL);
    return uarray2->width;
}

/* Returns the height of the 2D UArray */
extern int UArray2_height (T uarray2) {
    assert(uarray2 != NULL);
    return uarray2->height;
}

/* Returns a void* pointing to the element in the 2D Uarray at 
   position (column, row) */
extern void *UArray2_at (T uarray2, int column, int row) {
    assert(column >= 0 && column < uarray2->width);
    assert(row >= 0 && row < uarray2->height);        
    assert(uarray2 != NULL);

    return UArray_at(uarray2->uarray, ((uarray2->width * row) + column)); 
}

/* Calls the apply function for all elements in the 2D UArray according to 
   row major */
extern void UArray2_map_row_major  (T uarray2, void apply(int i, int j, 
    T uarray2, void *p1, void *p2), void *cl) {

    assert(uarray2 != NULL);
    assert(uarray2->uarray != NULL);
    assert(apply != NULL);
    
    for(int j = 0; j < (uarray2->height); j++) {
        for(int i = 0; i < (uarray2->width); i++) {
            void* p1 = UArray2_at(uarray2, i, j);
            apply(i, j, uarray2, p1, cl);
        }
    }
}

/* Calls the apply function for all elements in the 2D UArray according to 
   column major */
extern void UArray2_map_col_major  (T uarray2, void apply(int i, int j, 
    T uarray2, void *p1, void *p2), void *cl) {
    
    assert(uarray2 != NULL);
    assert(uarray2->uarray != NULL);
    assert(apply != NULL);

    for(int i = 0; i < (uarray2->width); i++) {
        for(int j = 0; j < (uarray2->height); j++) {
            void* p1 = UArray2_at(uarray2, i, j);
            apply(i, j, uarray2, p1, cl);
        }
    }
}


