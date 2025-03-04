/*
 *                      bit2.c
 *
 *         This file provides the interface of the Bit2 data
 *         structure. Bit2 is a two dimensional Bit Vector. 
 *         
 *         Author: Cheryl Melwani (cmelwa01) and Anna Wang (awang15)
 *         Date: February 21st 2021
 *
 */
 
#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T; 


/*
Name: UArray2_new
Description: Allocates, initializes and returns a new 2D bit vector of 
             width * height elements, with bounds 0 to (width * height - 1) 
             elements. 
Expectations of input: Parameters width and height has to be 0 or greater. 
             A checked runtime error is produced if any of the inputs fail 
             to follow these expectations.
Expectations of output: Pointer (Type T) to new 2D bit vector.
*/
extern T     Bit2_new  (int width, int height);

/*
Name: Bit2_free
Description: Deallocates and clears the array itself and the 
T structure.
Expectations of input: Accepts null pointers.
Expectations of output: Void. Memory is freed. 
*/
extern void  Bit2_free  (T *Bit2);

/*
Name: Bit2_width
Description: Returns the width (number of columns in the 2D bit vector)
Expectations of input: bit2vector is nonnull. Checked runtime error is
             raised if any of the inputs fail to follow these expectations.
Expectations of output: Integer denoting width of the 2D bit vector
*/
extern int   Bit2_width  (T Bit2);

/*
Name: Bit2_height
Description: Returns the height (number of rows in the 2D bit vector)
Expectations of input: bit2vector is nonnull. Checked runtime error is
             raised if any of the inputs fail to follow these expectations.
Expectations of output: Integer denoting height of the 2D bit vector
*/
extern int   Bit2_height  (T Bit2);

/*
Name: Bit2_put
Description: Returns the bit at (column, row) if it does exist
Expectations of input: Row and column must be nonnegative integers, 
    and bit2vector is nonnull. 
Expectations of output: Returns the previous element found in 
        column, row) in the bit2vector.
*/
extern int   Bit2_get  (T Bit2, int column, int row);

/*
Name: Bit2_put
Description: Finds element in (column, row) and sets that element to bit.
Bit2_put returns the previous value of element (column, row).
Expectations of input: Row and column be nonnegative integers, bit2vector is 
        nonnull and bit is either equal to 0 or 1.
Expectations of output: Returns the previous element found in 
        column, row) in the bit2vector.
*/
extern int   Bit2_put  (T Bit2, int column, int row, int bit);  

/*
Name: Bit2_map_row_major
Description: Bit2_map_row_major calls the function pointed to by apply for 
            every element in the 2D uarray in row major order where column 
            indices vary more rapidly than row indices. Clients can pass an 
            application-specific pointer, cl, to UArray_map_row_major and this
            pointer is passed along to apply at each call.
Expectations of input: A nonnull bit2array
Expectations of output: Void. Function apply() gets applied to all elements in 
            the 2D bit vector.
*/
extern void Bit2_map_row_major  (T Bit2, void apply(int i, int j, 
    Bit2_T a, int b, void *p1), void *cl);

/*
Name: Bit2_map_col_major
Description: Bit2_map_col_major calls the function pointed to by apply for 
            every element in the 2D uarray in column major order where row 
            indices vary more rapidly than column indices. Clients can pass an 
            application-specific pointer, cl, to UArray_map_col_major and this
            pointer is passed along to apply at each call.
Expectations of input: A nonnull bit2array
Expectations of output: Void. Function apply() gets applied to all elements in 
            the 2D bit vector.
*/
extern void Bit2_map_col_major  (T Bit2, void apply(int i, int j, 
    Bit2_T a, int b, void *p1), void *cl);

#undef T

#endif