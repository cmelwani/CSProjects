/******************************************************************************
 *                            pack.c                                          *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation responsible for the  *
                 packing of quantized DCT values (unsigned/signed ints) into  *
                 a 32-bit codeword, as well as the corresponding unpacking    *
                 using our bitpack interface                                  *
                                                                              *
 *****************************************************************************/
#include "pack.h"

/*------------------------- COMPRESSION FUNCTIONS --------------------------*/

/*
 Name: pack
 Parameters: apply function parameters as specified by the a2methods 
             file. Applied onto a 2D Array that stores the 32 bit words  
             and a closure argument that holds dct quantized pixels.
 Return: void 
 Purpose: to pack the dctQuantized values (a,b,c,d,avgPb,avgPr) into a 
            32-bit codeword using the bitpack program. 
 */
void pack(int i, int j, A2 words, 
                A2Methods_Object *elem, void *dctQuantized) 
{
    (void) words;
    cv input = (cv) dctQuantized;
    dctQ currPix = input->methods->at(input->pixels, i, j);
    uint32_t codeword = 0;

    codeword = Bitpack_newu(codeword, 4, 0, currPix->avgPr);
    codeword = Bitpack_newu(codeword, 4, 4, currPix->avgPb);
    codeword = Bitpack_news(codeword, 6, 8, currPix->d);
    codeword = Bitpack_news(codeword, 6, 14, currPix->c);
    codeword = Bitpack_news(codeword, 6, 20, currPix->b);
    codeword = Bitpack_newu(codeword, 6, 26, currPix->a);

    *(uint32_t *)elem = codeword;
}

/*----------------------- DECOMPRESSION FUNCTIONS --------------------------*/

/*
 Name: unpack
 Parameters: apply function parameters as specified by the a2methods 
             file. Applied onto a 2D Array that stores the 32 bit words  
             and a closure argument that holds dct quantized pixels.
 Return: void 
 Purpose: to unpack the 32-bit codeword and convert it back to the 
            dctQuantized values (a,b,c,d,avgPb, avgPr) using the bitpack 
            program
 */
void unpack(int i, int j, A2 words, 
                A2Methods_Object *elem, void *dctQuantized) 
{
    (void) words;
    cv input = (cv) dctQuantized;
    uint32_t word = (*(uint32_t *)elem);
    dctQ currPix = input->methods->at(input->pixels, i, j);

    currPix->avgPr = Bitpack_getu(word, 4, 0);
    currPix->avgPb = Bitpack_getu(word, 4, 4);
    currPix->d = Bitpack_gets(word, 6, 8);
    currPix->c = Bitpack_gets(word, 6, 14);
    currPix->b = Bitpack_gets(word, 6, 20);
    currPix->a = Bitpack_getu(word, 6, 26);

}


