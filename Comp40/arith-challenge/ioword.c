/******************************************************************************
 *                            ioword.c                                        *
 *                                                                            *
* Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                  *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implemenation responsible for the   *
                 reading in the code word from a compressed image, as well as *
                 outputing codeword into a compressed image, using our        *
                 bitpack interface                                            *
                                                                              *
 *****************************************************************************/
#include "ioword.h"

/*
 Name: printWord
 Parameters: 2D array that stores the 32 bit words, width and height 
            of the original pixmap and the a2 methods suite.
 Return: void 
 Purpose: Prints out the header for the compressed image, and then
        calls the mapping function to use printHelper to print out 
        each codeword
 */
void printWord(A2 words, unsigned width, unsigned height, A2Methods_T methods)
{
    printf("COMP40 Compressed image format 2\n%u %u\n", width, height);
    methods->map_row_major(words, printHelper, NULL);

}

/*
 Name: printHelper
 Parameters: Apply function parameters as specified by the a2methods 
             file. Applied onto a 2D Array that stores the 32 bit words  
             and a closure argument that is voided.
 Return: void
 Purpose: Helper function that gets each byte of the 32 bit code word 
            and prints it out in big endian order using putchar().
 */
void printHelper(int i, int j, A2 words,
                A2Methods_Object *elem, void *cl) 
{
    (void)i;
    (void)j;
    (void)words;
    (void)cl;
    uint32_t codeword = *(uint32_t *)elem;

    for (int x = 3; x >= 0; x--){
        uint64_t byte = Bitpack_getu(codeword, 8, x * 8);
        putchar(byte);
    }
}

/*
 Name: readWord
 Parameters: apply function parameters as specified by the a2methods 
             file. Applied onto a 2D Array that stores the 32 bit words  
             and a closure argument holding a file pointer to the 
             given file (compressed ppm)
 Return: void 
 Purpose: Reads each codeword and updates the specified fields 
            in the 32-bit word using the bitpack program. It 
            populates the A2 word array with 32 bit words
            from the compressed ppm.
 */
void readWord(int i, int j, A2 words,
                A2Methods_Object *elem, void *fp)
{
    (void)i;
    (void)j;
    (void)words;
    uint64_t codeword = 0;
    FILE *input = (FILE *) fp;

    for (int x = 3; x >= 0; x--){
        uint64_t c = fgetc(input);
        assert(c != ((unsigned) EOF));
        codeword = Bitpack_newu(codeword, 8, x * 8, c);
    }

    *(uint32_t *) elem = codeword;
}




