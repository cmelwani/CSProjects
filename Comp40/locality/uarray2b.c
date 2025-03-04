/*
 *                      uarray2b.c
 *
 *         This program handles the implementation of a 2 dimensional
 *         blocked array
 *   
 *         Author: Cheryl Melwani and Devan Venkataraman
 *         Date: March 8th 2021
 *
 */
 
#include <string.h>
#include "uarray2b.h"
#include <uarray2.h>
#include <uarray.h>
#include <assert.h>
#include "mem.h"
#include <stdio.h>
#include <math.h>

#define T UArray2b_T

struct UArray2b_T {
    int width;
    int height;
    int size;
    int blocksize; 
    UArray2_T uarray2;
};

/* allocate_mem_block
 * Description: Allocates memory for each block in the blocked array.
 * Is an apply function that's called in UArray2b_new
 * Input Expectation: none
 * Output Expectation: void
 */
void allocate_mem_block(int col, int row, UArray2_T uarray2, 
                        void *elem, void *cl) 
{
    (void) col;
    (void) row;
    (void) uarray2;

    T array2b = cl;
    int length = array2b->blocksize * array2b->blocksize;
    int size = array2b->size;
    *(UArray_T*) elem = UArray_new(length, size);
}

/* UArray2b_new
 * Description: Allocates memory and initializes a new UArray2b
 * with width * height elements. Each block has a size of blocksize
 * and each element in the block has a size of size. 
 * Input Expectation: Expect size and blocksize are greater than 0, 
 * width and height are greater than or equal to 0.
 * Output Expectation: Should return the new UArray2b created
 */
extern T UArray2b_new (int width, int height, int size, int blocksize)
{
    assert(size > 0);
    assert(blocksize > 0);
    assert(width >= 0 && height >= 0);

    /* create and intialize a uarray2b */
    T array2b;
    NEW(array2b);
    array2b->width = width;
    array2b->height = height;
    array2b->size = size;
    array2b->blocksize = blocksize;

    int uarray2_width = ceil((double)width / blocksize);
    int uarray2_height = ceil((double)height / blocksize);
    int uarray2_size = blocksize * blocksize * size;
    array2b->uarray2 = UArray2_new(uarray2_width, 
                                   uarray2_height, uarray2_size);
    UArray2_map_row_major(array2b->uarray2, allocate_mem_block, array2b);

    return array2b;
}

/* UArray2b_new_64K_block
 * Description: Changes the blocksize of the 2D Array to equal 64K.
 * If the size of an element is greater than 64K, blocksize is equal
 * to 1.
 * Input Expectation: Size is non-zero. Width and height are non-negative.
 * Output Expectation: Should return the new UArray2b created
 */
extern T UArray2b_new_64K_block(int width, int height, int size)
{
    int blocksize = 0;
    assert(size > 0);
    if (size > 65536) {
        blocksize = 1;
    } else {
        blocksize = sqrt(65536 / size);
    }
    return UArray2b_new(width, height, size, blocksize);
}

/* free_mem_block
 * Description: Apply function that frees each block in the 2D Array
 * Input Expectation: none
 * Output Expectation: void
 */
void free_mem_block(int col, int row, UArray2_T uarray2,
                    void *elem, void *cl) 
{
    (void) col;
    (void) row;
    (void) uarray2;
    (void) cl;
    UArray_free((UArray_T*)elem);
}

/* UArray2b_free
 * Description: Frees all memory associated with the UArray2b structure.
 * Input Expectation: array2b pointer and contents are non-NULL
 * Output Expectation: Frees the contents of UArray2b's array,
 * the array itself, and the struct itself. 
 */
extern void UArray2b_free (T *array2b) 
{
    assert(array2b != NULL);
    assert(*array2b != NULL); 

    /* free the blocks */
    UArray2_map_row_major((*array2b)->uarray2, free_mem_block, NULL);
    /* free the uarray2 */
    UArray2_free(&((*array2b)->uarray2));
    /* free the struct */
    FREE(*array2b);
}

/* UArray2b_width
 * Description: Simple getter that returns the array's width.
 * Input Expectation: array2b is non-NULL
 * Output Expectation: returns array's width.
 */
extern int UArray2b_width (T array2b) 
{
    assert(array2b != NULL);
    return array2b->width;
}

/* UArray2b_height
 * Description: Simple getter that returns the array's height.
 * Input Expectation: array2b is non-NULL
 * Output Expectation: returns array's height.
 */
extern int UArray2b_height (T array2b) 
{
    assert(array2b != NULL);
    return array2b->height;
}

/* UArray2b_size
 * Description: Simple getter that returns the array's size.
 * Input Expectation: array2b is non-NULL
 * Output Expectation: returns array's size.
 */
extern int UArray2b_size (T array2b)
{
    assert(array2b != NULL);
    return array2b->size;
}

/* UArray2b_blocksize
 * Description: Simple getter that returns the array's blocksize.
 * Input Expectation: array2b is non-NULL
 * Output Expectation: returns array's blocksize.
 */
extern int UArray2b_blocksize(T array2b)
{
    assert(array2b != NULL);
    return array2b->blocksize;
}

/* UArray2b_at
 * Description: Returns a pointer to the element stored in the
 * array at the provided column and width
 * Input Expectation: array2b is non-NULL. Column and row index values
 * passed are both non-negative and within 0 and the width and height
 * of the array respectively
 * Output Expectation: returns pointer to the element stored in the
 * array at the provided column and width
 */
extern void *UArray2b_at(T array2b, int column, int row)
{
    assert(array2b != NULL);
    assert(column >= 0 && column < array2b->width);
    assert(row >= 0 && row < array2b->height); 

    int block_i = column / (array2b->blocksize);
    int block_j = row / (array2b->blocksize);
    UArray_T *curr_block = UArray2_at(array2b->uarray2, block_i, block_j);

    int index = array2b->blocksize * (row % array2b->blocksize) 
        + (column % array2b->blocksize);
    return UArray_at(*curr_block, index);
}

/* UArray2b_map
 * Description: Map's over all elements in all blocks using map-major
 * order. 
 * Input Expectation: Non-null array2b, non-null uarray2, non-null apply
 * function.
 * Output Expectation: void 
 */
extern void UArray2b_map(T array2b,
                          void apply(int col, int row, T array2b,
                                     void *elem, void *cl), void *cl)
{
    assert(array2b != NULL);
    assert(array2b->uarray2 != NULL);
    assert(apply != NULL);
    
    for (int j = 0; j < UArray2b_height(array2b); j++) {
        for (int i = 0; i < UArray2b_width(array2b); i++) {
            void *elem = UArray2b_at(array2b, i, j);
            apply(i, j, array2b, elem, cl);
        }
    }    
}