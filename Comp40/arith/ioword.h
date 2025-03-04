/******************************************************************************
 *                            ioword.h                                        *
 *                                                                            *
* Authors:    Anna Wang (awang15), Cherly Melwani (cmelwa01)                  *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the interface responsible for the       *
                 reading in the code word from a compressed image, as well as *
                 outputing codeword into a compressed image, using our        *
                 bitpack interface                                            *
                                                                              *
 *****************************************************************************/

#include "pack.h"

#define A2 A2Methods_UArray2 /* private abbrev*/

void printWord(A2 words, unsigned width, unsigned height, A2Methods_T methods);
void printHelper(int i, int j, A2 words,
                A2Methods_Object *elem, void *cl);
void readWord(int i, int j, A2 words,
                A2Methods_Object *elem, void *fp);
