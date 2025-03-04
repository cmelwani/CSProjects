/******************************************************************************
 *                            ppmdiff.c                                       *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani                    *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: Arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation                      *
 *                                                                         *
 *****************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "compress40.h"
#include "math.h"

#include <pnm.h>

#include "a2methods.h"
#include "a2plain.h"

#define A2 A2Methods_UArray2

int main(int argc, char *argv[]) {

    A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);
    
    FILE *fp; 
    FILE *fp2;
    fp = fopen(argv[1], "rb");
    fp2 = fopen(argv[2], "rb");
    
    Pnm_ppm input1 = Pnm_ppmread(fp, methods);
    Pnm_ppm input2 = Pnm_ppmread(fp2, methods);

    int diffw = input1->width - input2->width;
    int diffh = input1->height - input2->height;
    if( (abs(diffw)) > 1 || (abs(diffh) > 1)){
        fprintf(stdout, "1.0\n");
        fprintf(stderr, "Error: Difference is too big in width and height!\n");
        exit(EXIT_FAILURE);
    }
    
    int w = 0; 
    int h = 0; 
    double sum = 0;
    double total = 0;
    double den1 = input1->denominator;
    double den2 = input2->denominator;

    if( input1->width >= input2->width ){
        w = input2->width;
    } else{
        w = input1->width;
    }
    
    if (input1->height >= input2->height ){
        h = input2->height;
    } else {
        h = input1->height;
    }

    for (int i = 0 ; i < w ; i ++){
        for (int j = 0; j < h ; j++){
            Pnm_rgb temp1 = input1->methods->at(input1->pixels, i, j);
            Pnm_rgb temp2 = input2->methods->at(input2->pixels, i, j);

            sum = pow(((temp1->red / den1) - (temp2->red / den2)), 2) 
            + pow(((temp1->green / den1) - (temp2->green / den2)), 2)
            + pow(((temp1->blue / den1) - (temp2->blue / den2)), 2);
            
            total += sum;

        }
    }
    total = total / ( 3 * w * h);
    total = sqrt(total);

    printf("E = %f\n", total);
    
    (void) argc;

    fclose(fp);
    fclose(fp2);
}