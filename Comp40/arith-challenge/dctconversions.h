/******************************************************************************
 *                            dctconversions.h                                *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March 24, 2020                                                 *
 * Course:     Comp 40                                                        *
 * Assignment: Arith                                                          *
 *                                                                            *
 * Description: This program contains the interface for the DCT conversions   *
                that carries out discrete cosine transformations (dct) on     *
                component video representations (Y/Pb/Pr values), and the     *
                reverse transformations for decompression. Prepares the DCT   *
                values (a,b,c,d,avgPb,abgPr) by making sure they are within   *
                range (i.e. +0.3 and -0.3)                                    *
                                                                              *
 *****************************************************************************/
#include "cvconversions.h"

#define A2 A2Methods_UArray2 /* private abbrev*/

#ifndef DCTCONVERSIONS
#define DCTCONVERSIONS

/* struct dctF
 * Holds float values a, b, c, d, avgPb, avgPr, representing a DCT pixel 
 */
typedef struct dctF {
    float a, avgPb, avgPr, b, c, d;
} *dctF;

void cvToDCT(int i, int j, A2 dct,
                A2Methods_Object *elem, void *cvImg);
float avgP(float p1, float p2, float p3, float p4);
void pixToDCT(float y1, float y2, float y3, float y4, dctF elem);
void dctToCV(int i, int j, A2 dct,
                A2Methods_Object *elem, void *cvImg);
void dctToPix( xyz pix1 , xyz pix2, xyz pix3, xyz pix4, dctF elem);
void checkRange(dctF elem);
float rangeHelper(float x, float MAX, float MIN);

#endif
