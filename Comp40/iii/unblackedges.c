/*
 *                      unblackedges.c
 *
 *         This program removes black edges from a scanned image in 
 *         bitmap format.
 *         
 *         Command line:   unblackedges.c [pbmfile]
 *         If no filename is supplied, the image is read from stdin.
 *
 *         Author: Anna Wang and Cheryl Melwani
 *         Date: February 26th 2021
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pnmrdr.h>
#include <stdbool.h>
#include <seq.h>
#include <bit2.h>
#include <bit.h>
#include "assert.h"

struct currLoc{
    int column;
    int row;
};

FILE *getFile (char *fileName);
void closeFile(FILE *inputFile);
Bit2_T pbmread (FILE *inputfd);
void removeBlack (Bit2_T bit2array);
void findSource(int constant, int dimension, Bit2_T bitmap);
void bfsRemove (Bit2_T bitmap, int i, int j );
void print(int i, int j, Bit2_T a, int b, void *p1);
void pbmwrite(FILE *outputfp, Bit2_T bitmap);


int main( int argc, char *argv[]) 
{
    FILE *fp;
    assert(argc <= 2);
    char *fileName;
    
    if (argc == 2) {
        fileName = argv[1];
    }
    
    fp = getFile(fileName);

    Bit2_T bitmap;
    bitmap = pbmread(fp);
    removeBlack(bitmap);
    pbmwrite(stdout, bitmap);

    Bit2_free(&bitmap);
    return EXIT_SUCCESS;
}

/* Opens input file named on command line. If no filenames given,
 * read in image from stdin.  */
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

/* Closes the file if pbm is not read in from
   standard input */
void closeFile(FILE *inputFile) 
{
    if (inputFile != stdin) {
        assert(fclose(inputFile) == 0);
    }
}

/* Checks the type of file provided and populates 
the bit2Array with the contents of the pbm file */
Bit2_T pbmread (FILE *inputfd) 
{
    Pnmrdr_T rdr = Pnmrdr_new(inputfd); 
    Pnmrdr_mapdata rdr_data = Pnmrdr_data(rdr);

    if(rdr_data.type != 1) { 
        fprintf(stderr, "%s\n", "Error: File is not PBM format");
        exit(EXIT_FAILURE);
    }

    int width = rdr_data.width;
    int height = rdr_data.height;
    Bit2_T bit2array = Bit2_new(width, height);

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            int bit = Pnmrdr_get(rdr);
            Bit2_put(bit2array, i, j, bit);
        }
    }

    Pnmrdr_free(&rdr);
    closeFile(inputfd);
    return bit2array;
}

/* Removes all of the black edge pixels in the pbm and converts it to 
white pixels. Calls findSource that finds the starting black pixel by 
checking the top, right, left, and bottom border */
void removeBlack (Bit2_T bitmap) 
{
    //traverse borders to find a black pixel  
    //1 corresponds to height, and 0 corresponds to width
    findSource(0, 0, bitmap);
    findSource((Bit2_height(bitmap)-1), 0, bitmap);
    findSource(0, 1, bitmap);
    findSource((Bit2_width(bitmap)-1), 1, bitmap);
}

/* Finds the starting black pixel by iterating through the 
borders of the bitmap file. Calls bfsRemove to start converting 
black pixels to white pixels */
void findSource(int constant, int dimension, Bit2_T bitmap) 
{
    if(dimension) {
        dimension = Bit2_height(bitmap); 
        for(int i = 0; i < dimension; i++) {
            //row is changing and column stays constant (0,1) (0,2) (0,3)
            if(Bit2_get(bitmap, constant, i)) { 
                bfsRemove(bitmap, constant, i);
            }
        }
    } else {
        dimension = Bit2_width(bitmap);
        for(int i = 0; i < dimension; i++) {
            //column is changing and row stays constant (1,0) (2,0) (3,0)
            if(Bit2_get(bitmap, i, constant)) { 
                bfsRemove(bitmap, i, constant);
            }
        }
    }
}

/* Using a similar strategy to the Breadth First Search (BFS) 
algorithm, the function finds all black edge pixels and converts them 
into white pixels */
void bfsRemove (Bit2_T bitmap, int column, int row) 
{
    //explore all neighbors, push each neighbor onto queue, repeat. 

    Seq_T queue = Seq_new(1000); 
    struct currLoc *currBit = malloc(sizeof(struct currLoc));
    currBit->column = column;
    currBit->row = row;
    Bit2_put(bitmap, currBit->column, currBit->row, 0);
    Seq_addhi(queue, currBit);

    while (Seq_length(queue) > 0) {
        struct currLoc *pop = Seq_get(queue, 0);
        Seq_remlo(queue);
        
        /*conditionals to make sure the program doesn't try to 
        access pixels that are outside the borders */
        if (pop->column+1 < Bit2_width(bitmap)) {
            if(Bit2_get(bitmap, (pop->column+1), pop->row)) {
                struct currLoc *temp = malloc(sizeof(struct currLoc));
                temp->column = pop->column + 1;
                temp->row = pop->row;
                Bit2_put(bitmap, temp->column, temp->row, 0);
                Seq_addhi(queue, temp);
            }
        }
        
        if (pop->column-1 >= 0) {
            if(Bit2_get(bitmap, (pop->column-1), pop->row)) {
                struct currLoc *temp = malloc(sizeof(struct currLoc));
                temp->column = pop->column - 1;
                temp->row = pop->row;
                Bit2_put(bitmap, temp->column, temp->row, 0);
                Seq_addhi(queue, temp);
            }
        }

        if (pop->row+1 < Bit2_height(bitmap)) {
            if(Bit2_get(bitmap, pop->column, (pop->row+1))) {
                struct currLoc *temp = malloc(sizeof(struct currLoc));
                temp->column = pop->column;
                temp->row = pop->row + 1;
                Bit2_put(bitmap, temp->column, temp->row, 0);
                Seq_addhi(queue, temp);
            }
        }

        if(pop->row-1 >= 0) {
             if(Bit2_get(bitmap, pop->column, (pop->row-1))) {
                struct currLoc *temp = malloc(sizeof(struct currLoc));
                temp->column = pop->column;
                temp->row = pop->row - 1;                
                Bit2_put(bitmap, temp->column, temp->row, 0);
                Seq_addhi(queue, temp);
            }
        }
        free(pop);
    }

    Seq_free(&queue);
}

/* Outputs the image with black edges removed to stdin in plain PBM 
 * format. */
void pbmwrite(FILE *outputfp, Bit2_T bitmap)
{
    (void) outputfp;
    fprintf(stdout,"P1\n");
    fprintf(stdout,"# Output PBM Using Unblackedges!\n"); 
    fprintf(stdout, "%i %i\n", Bit2_width(bitmap), Bit2_height(bitmap));
    Bit2_map_row_major(bitmap, print, NULL);
}

/* Prints on stdout the output of our program. Conforms to 70 
*   character rule*/
void print(int i, int j, Bit2_T a, int b, void *p1) 
{
    (void)j;
    (void)p1;
    
    /* 70 characters rule*/
    if( (i > 0) && ((i % 70) == 0) ) {
        fprintf(stdout,"\n");
    } 
    
    fprintf(stdout,"%i", b);
    if(i == Bit2_width(a) - 1) {
        fprintf(stdout,"\n");
    }
}