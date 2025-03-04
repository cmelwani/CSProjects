/******************************************************************************
 *                            cvconversions.h                                 *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cherly Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the interface for the 2 way conversions * 
                between RGB and component video representation.               * 
                                                                              *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "arith40.h"

#define A2 A2Methods_UArray2 /* private abbrev*/

#ifndef CONVERSIONS
#define CONVERSIONS

/* struct xyz
 * Holds float values Y,Pb,Pr, representing a component video pixel 
 */
typedef struct xyz{
    float Y, Pb, Pr;
} *xyz;

/* struct cv
 * Holds a 2D array (type A2) used to represent a pixmap and A2 methods suite 
 */
typedef struct cv{
    A2Methods_T methods;
    A2 pixels;
} *cv;

void rgbToCv(int i, int j, A2 cvImg, 
                 A2Methods_Object *elem, void *inputImg);
void cvCalc(float r, float g, float b, xyz elem);
void cvToRgb(int i, int j, A2 cvImg,
                A2Methods_Object *elem, void *outputImg);
void rgbCalc(float Y, float Pb, float Pr, Pnm_rgb currPix);
float scaleRGB(float rgb);

#endif