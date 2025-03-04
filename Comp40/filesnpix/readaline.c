/* Created by: Anna Wang and Cheryl Melwani */
/* February 5th 2021 */

#include <readaline.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Name: readaline() 
   Function: reads a single line from an input file (max 200 characters) */
size_t readaline(FILE *inputfd, char **datapp)
{    
    assert(inputfd != NULL || datapp != NULL); // how to test this
    assert(!ferror(inputfd));

    char c;
    int numBytes = 0;
    char *arrBytes = (char *) malloc(200 * sizeof(char));
    assert(arrBytes != NULL); 

    int eof = fgetc(inputfd);
    if(eof == EOF){
        free(arrBytes);
        *datapp = NULL;
        return 0;
    } else {
        ungetc(eof, inputfd);
    }

    while((c = getc(inputfd)) != '\n' && c != EOF) { 
        arrBytes[numBytes] = c; 
        numBytes++;
        if(numBytes == 200){
            fprintf(stderr, "readaline: input line too long\n");
            exit(4);
        }
    }

    arrBytes[numBytes] = c;
    numBytes++;
    *datapp = arrBytes;
    
    return numBytes;
}