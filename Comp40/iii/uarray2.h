/*
 *                      uarray2.h
 *
 *         This file provides the interface of the UArray2 data
 *         structure. UArray2 is a two dimensional UArray. 
 *         
 *         Author: Cheryl Melwani (cmelwa01) and Anna Wang (awang15)
 *         Date: February 21st 2021
 *
 */
 
#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T; 

/*
Name: UArray2_new
Description: Allocates, initializes and returns a new 2D array of width * 
             height elements, with bounds 0 to (width * height - 1) 
             elements. If length * width = 0, the array has no elements. 
             Each element occupies size bytes. Each 2D array is represented 
             as a single Hanson's UArray_T. 
Expectations of input: Parameters width and height has to be 0 or greater, 
            and size has to be positive. A checked runtime error is produced 
            if any of the inputs fail to follow these expectations.
Expectations of output: Pointer (Type T) to new 2D unboxed array with 
            size * (width * height) bytes of memory allocated.
*/
extern T     UArray2_new  (int width, int height, int size);

/*
Name: UArray2_free
Description: Deallocates and clears the array itself and the 
T structure.
Expectations of input: Accepts null pointers.
Expectations of output: Void. Memory is freed. 
*/
extern void  UArray2_free  (T *uarray2);

/*
Name: UArray2_size
Description: Returns the size of elements in a UArray2_T
Expectations of input: uarray2 or *urray2 is nonnull. Checked runtime 
                error is raised if any of the inputs fail to follow these 
                expectations.
Expectations of output: Integer denoting the byte value of elements 
                in the array.
*/
extern int   UArray2_size  (T uarray2);

/*
Name: UArray2_width
Description: Returns the width (number of columns in the 2D uarray) 
Expectations of input: uarray2 or *urray2 is nonnull. Checked runtime 
        error is raised if any of the inputs fail to follow these 
        expectations.
Expectations of output: Integer denoting width of the 2D uarray
*/
extern int   UArray2_width  (T uarray2);

/*
Name: UArray2_height
Description: Returns the height (number of rows in the 2D uarray)
Expectations of input: uarray2 or *urray2 is nonnull. Checked runtime 
        error is raised if any of the inputs fail to follow these 
        expectations.
Expectations of output: Integer denoting height of the 2D uarray
*/
extern int   UArray2_height  (T uarray2);

/*
Name: UArray2_at
Description: Returns the element in the 2D uarray at index (row, column).
Expectations of input: Row and column be nonnegative integers and uarray2 is 
            nonnull.
Expectations of output: Returns a void pointer that points to the element
            at the location (row, column) in the uarray.
*/
extern void *UArray2_at  (T uarray2, int column, int row); 

/*
Name: UArray_map_row_major
Description: UArray_map_row_major calls the function pointed to by apply for 
            every element in the 2D uarray in row major order where column 
            indices vary more rapidly than row indices. Clients can pass an 
            application-specific pointer, cl, to UArray_map_row_major and 
            this pointer is passed along to apply at each call. 
Expectations of input: A nonnull uarray2
Expectations of output: Void. Function apply() gets applied to all elements in 
            the 2D array.
*/
extern void UArray2_map_row_major  (T uarray2, void apply(int i, int j, 
    T uarray2, void *p1, void *p2), void *cl);

/*
Name: UArray2_map_col_major
Description: UArray_map_col_major calls the function pointed to by apply for 
            every element in the 2D uarray in column major order where row 
            indices vary more rapidly than column indices. Clients can pass an 
            application-specific pointer, cl, to UArray_map_col_major and this
            pointer is passed along to apply at each call.
Expectations of input: A nonnull uarray2
Expectations of output: Void. Function apply() gets applied to all elements in 
            the 2D array.
*/
extern void UArray2_map_col_major  (T uarray2, void apply(int i, int j, 
    T uarray2, void *p1, void *p2), void *cl);

#undef T

#endif