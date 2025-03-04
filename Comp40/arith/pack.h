/******************************************************************************
 *                            pack.h                                          *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cherly Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the interface responsible for the       *
                 packing of quantized DCT values (unsigned/signed ints) into  *
                 a 32-bit codeword, as well as the corresponding unpacking    *
                 using our bitpack interface                                  *
                                                                              *
 *****************************************************************************/
#include "quantize.h"
#include "bitpack.h"

#define A2 A2Methods_UArray2 /* private abbrev*/

#ifndef PACK
#define PACK

void pack(int i, int j, A2 words, 
                  A2Methods_Object *elem, void *dctQuantized);
void unpack(int i, int j, A2 words, 
                  A2Methods_Object *elem, void *dctQuantized);

#endif