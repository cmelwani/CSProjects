/* Created by: Anna Wang and Cheryl Melwani */
/* February 5th 2021 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pnmrdr.h>

void calcAvg(Pnmrdr_T rdr);

/* Name: main() 
   Function: handles opening a file from the command line or 
   from standard input. Passes in that information into
   calcAvg() */
int main( int argc, char *argv[])
{
    FILE *fp;
    if (argc == 2) {
        /* extern const Except_T Pnmrdr_Badformat; raised when not a pnm file */
        fp = fopen(argv[1], "rb");
        if(fp == NULL){
            fprintf(stderr, "%s: %s\n", "Error: Could not open file", argv[1]);
            exit(EXIT_FAILURE);
        } 

    } else if (argc > 2) {
        /* More than 1 argument given, brightness halts with an error */
        fprintf(stderr, "Error: More than one argument is given.\n");
        exit(EXIT_FAILURE);
        
    } else if (argc == 1) {
        /* If supplied graymap has a pixel count of 0, brightness 
        halts with an error */
        fp = stdin;
    }

    Pnmrdr_T rdr = Pnmrdr_new(fp); 
    calcAvg(rdr);
    Pnmrdr_free(&rdr);
    fclose(fp);
    return EXIT_SUCCESS;
}

/* Name: calcAvg() 
   Function: makes sure that given file is of pgm format and 
   calculates the average pixel brightness of that file */
void calcAvg(Pnmrdr_T rdr) {
    Pnmrdr_mapdata rdr_data = Pnmrdr_data(rdr);
    int typeOfFile = rdr_data.type; 

    if(typeOfFile != 2) {
        fprintf(stderr, "%s\n", "Error: File is not PGM format");
        exit(EXIT_FAILURE);
    }

    int width = rdr_data.width;
    int height = rdr_data.height;
    float pixel = 0;
    float average = 0;

    for(int i = 0; i < (width*height); i++) {
        pixel += Pnmrdr_get(rdr);
    }

    average = (pixel / (width*height));
    printf("Average Brightness: %.3f\n", average);
}
