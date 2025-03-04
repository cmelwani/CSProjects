/******************************************************************************
 *                            quantize.h                                      *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the interface responsible for the       *
                 quantization of DCT floating point values into signed and    *
                 unsigned integers, and the inverse conversions.              * 
                                                                              *
 *****************************************************************************/
#include "dctconversions.h"

#define A2 A2Methods_UArray2 /* private abbrev*/

#ifndef QUANTIZE
#define QUANTIZE

/* struct dctQ
 * Holds unsigned values a, avgPb, avgPr and signed values b,c,d. 
 * Represents a quantized DCT pixel that holds information about a 
 * 2*2 block of rgb/xyz pixel
 */
typedef struct dctQ {
    unsigned a, avgPb, avgPr;
    signed b, c, d;
} *dctQ;

void quantizeDCT(int i, int j, A2 dctQuantized,
                A2Methods_Object *elem, void *dctFloat);
unsigned quantizeA(float x);
signed quantizeBCD(float x);
void unquantizeDCT(int i, int j, A2 dctF,
                A2Methods_Object *elem, void *dctQ);
float unquantizeA(unsigned x);
float unquantizeBCD(signed x);

#endif