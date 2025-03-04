/*
 *                      sudoku.c
 *
 *         This program checks if a sudoku puzzle is solved
 *
 *         Command line:   sudoku [pgmfile]
 *         If no filename is supplied, the image is read from stdin.
 *         
 *         Author: Cheryl Melwani (cmelwa01) and Anna Wang (awang15)
 *         Date: February 26th 2021
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <uarray2.h>
#include <uarray.h>
#include "assert.h"
#include "pnmrdr.h"

FILE *getFile (char *fileName);
void closeFile(FILE *inputFile);
UArray2_T pgmRead (FILE *inputfd, UArray2_T sudoku);
void checkSudoku(UArray2_T sudoku);
void checkRow(int column, int row, UArray2_T sudoku, void *p1, void *p2);
void checkCol(int i, int j, UArray2_T sudoku, void *p1, void *p2);
void checkChunk(int column, int row, UArray2_T sudoku);


int main( int argc, char *argv[]) 
{
    FILE *fp;
    assert(argc <= 2);
    char *fileName;

    if (argc == 2) {
        fileName = argv[1];
    }
    
    /*Open input file if given, otherwise read from stdin */
    fp = getFile(fileName);
    UArray2_T sudoku = UArray2_new(9, 9, sizeof(int));

    /*Read input file using Pnmrdr and store into our 
    uarray2 sudoku*/
    pgmRead(fp, sudoku);

    /*Check sudoku to see if it is correctly solved*/
    checkSudoku(sudoku);
    return 0;
}

/* Opens input file named on command line. If no filenames 
given, read in image from stdin.  */
FILE *getFile (char *fileName) 
{
    FILE *file;
    
    if (fileName != NULL) {
        file = fopen(fileName, "rb");
        assert(file != NULL);
    } else {
        file = stdin;
    }
    return file;
}

/* Reads image in input file using Pnmrdr and stores into 
 * our Uarray2. Makes sure that the image is a valid pgm
 * and a valid sudoku */
UArray2_T pgmRead (FILE *inputfd, UArray2_T sudoku ) 
{

    Pnmrdr_T rdr = Pnmrdr_new(inputfd); 
    Pnmrdr_mapdata rdr_data;
    rdr_data = Pnmrdr_data(rdr);

    /*input file must be gray map*/
    if(rdr_data.type != 2) { 
        exit(1);
    }

    /* checking if dimension of pgm is a 9x9 */
    if(rdr_data.width != 9 || rdr_data.height != 9) {
        exit(1);
    }
    
    /*reading and storing into uarray2 */
    for(int j = 0; j < 9; j++) {
        for(int i = 0; i < 9; i++) {
            int pixel = Pnmrdr_get(rdr);
            /* check if pixel has an intensity of zero or 
            greater than 9 */
            if(pixel == 0 || pixel > 9) {
                exit(1);
            }
            *(int*) UArray2_at(sudoku, i, j) = pixel;
        }
    }
    Pnmrdr_free(&rdr);
    closeFile(inputfd);
    return sudoku;
}

/* Closes input file*/
void closeFile(FILE *inputFile) 
{
    if (inputFile != stdin) {
        assert(fclose(inputFile) == 0);
    }
}

/* Checks to see if sudoku is solved or not. */
void checkSudoku(UArray2_T sudoku) 
{
    for(int j = 0; j < 9; j+=3) {
        for(int i = 0; i < 9; i+=3) {
            checkChunk(i, j, sudoku);
        }
    }
    /* Initialize uarray of length 9 filled with 0's. 
    *  keeps track of the frequencies of each number within a row.*/
    UArray_T rowCounter = UArray_new(9, sizeof(int));
    for(int i = 0; i < 9; i++) {
         (*(int*)UArray_at(rowCounter, i)) = 0;
    }
    UArray2_map_row_major(sudoku, checkRow, &rowCounter);

     /* Initialize uarray of length 9 filled with 0's */
    UArray_T colCounter = UArray_new(9, sizeof(int));
    for(int i = 0; i < 9; i++) {
        (*(int*)UArray_at(colCounter, i)) = 0;
    }
    UArray2_map_col_major(sudoku, checkCol, &colCounter);
    UArray_free(&rowCounter);
    UArray_free(&colCounter);
    UArray2_free(&sudoku);
}

/* Checks that there is is 1 instance of numbers 1-9 in every row. 
Returns 1 if not solved. */
void checkRow(int column, int row, UArray2_T sudoku, void *p1, 
    void *rowCounter) 
{

    (void) column; /* compiler requires to use all parameters*/
    
    int index = (*(int *) p1) - 1;
    int elem = (*(int *) UArray_at((*(UArray_T*) rowCounter), index));

    if(elem == row) {
        (*(int *) UArray_at((*(UArray_T*) rowCounter), index))++;
    } else {
        UArray_free((UArray_T*) rowCounter);
        UArray2_free(&sudoku);
        exit(1);
    }
}

/* Checks that there is is 1 instance of numbers 1-9 in every column. 
Returns 1 if not solved. */
void checkCol(int column, int row, UArray2_T sudoku, void *p1, 
    void *colCounter) 
{

    (void) row; /* compiler requires to use all parameters*/
    
    int index = (*(int *) p1) - 1;
    int elem = (*(int *) UArray_at((*(UArray_T*) colCounter), index));

    if(elem == column) {
        (*(int *) UArray_at((*(UArray_T*) colCounter), index))++;
    } else {
        UArray_free((UArray_T*) colCounter);
        UArray2_free(&sudoku);
        exit(1);
    }
}

/* Checks that there is is 1 instance of numbers 1-9 in every chunk. 
Returns 1 if not solved. */
void checkChunk(int column, int row, UArray2_T sudoku) 
{
    /*Initialize everything in frequency array to 0*/
    int numFreq[9];
    for(int i = 0; i < 9; i++) {
        numFreq[i] = 0;
    }

    for(int j = 0 ; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            int num = *((int *)UArray2_at(sudoku, column + i, row + j)) -1;
            numFreq[num]++;
        }
    }

    for(int i = 0; i < 9; i++) {
        if(numFreq[i] != 1) {
            exit(1);
        }
    }
}
