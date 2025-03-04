/******************************************************************************
 *                            compress40.c                                    *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation for image            *
                 compression and decompression. Specifically, it handles the  *
                 image conversions between full-color portable pixmap images  * 
                 and compressed binary image files                            *
                                                                              *
 *****************************************************************************/
#include "compress40.h"
#include "cvconversions.h"
#include "dctconversions.h"
#include "quantize.h"
#include "pack.h"
#include "ioword.h"
#define A2 A2Methods_UArray2

const int SCALE = 255;

void trim(Pnm_ppm input);

/*
 Name: compress40
 Parameters: A file pointer that points to the ppm image inputted by the 
 user
 Return: void
 Purpose: Compresses the image given on the input stream 
          and prints it on to standard output following the COMP40 compressed
          image format as specified. This function calls respective compress
          image functions to handle the compression.
 */
extern void compress40 (FILE *input) /* reads PPM, writes compressed image */
{ 
    assert(input != NULL);

    A2Methods_T methods = uarray2_methods_plain;
    assert(methods);
    
    /*Read in given ppm and trim image to even width and height*/
    Pnm_ppm inputImg = Pnm_ppmread(input, methods);
    trim(inputImg);
    
    /* Create instance of cv structs that hold A2 arrays and methods 
        for component video representation, dctfloat, and 
        dct quantized representations, respectively. */
    cv cvImg = malloc(sizeof(struct cv));
    cvImg->methods = methods;
    cvImg->pixels = methods->new(inputImg->width, inputImg->height, sizeof(struct xyz)); 

    cv dctFloat = malloc(sizeof(struct cv));
    dctFloat->methods = methods;
    dctFloat->pixels = methods->new(inputImg->width/2, inputImg->height/2, sizeof(struct dctF));

    cv dctQuantized = malloc(sizeof(struct cv));
    dctQuantized->methods = methods;
    dctQuantized->pixels = methods->new(inputImg->width/2, inputImg->height/2, sizeof(struct dctQ));
    
    /* 2D array that holds the codewords representing our compressed image */
    A2 words = methods->new(inputImg->width/2, inputImg->height/2, sizeof(uint32_t));
    
    /* Mapping functions that go through all the modules of image compression, finally
        printing out the compressed image to stdout */
    methods->map_row_major(cvImg->pixels, rgbToCv, inputImg);
    methods->map_row_major(dctFloat->pixels, cvToDCT, cvImg);
    methods->map_row_major(dctQuantized->pixels, quantizeDCT, dctFloat);
    methods->map_row_major(words, pack, dctQuantized);
    printWord(words, (unsigned )inputImg->width, (unsigned )inputImg->height, methods);

    /* freeing memory*/
    Pnm_ppmfree(&inputImg);
    methods->free(&words);
    methods->free(&dctQuantized->pixels);
    free(dctQuantized);
    methods->free(&dctFloat->pixels);
    free(dctFloat);
    methods->free(&cvImg->pixels);
    free(cvImg);
}

/*
 Name: trim
 Parameters: Pnm_ppm image 
 Return: void
 Purpose: Trims the edges of the ppm to even values if the 
          given width and height of the image are odd.
 */
void trim(Pnm_ppm input)
{
    if( (input->width <= 1) || (input->height <= 1) ){
        fprintf(stderr,"Error: Image is too small to be compressed\n");
        exit(EXIT_FAILURE);
    }
    if( (input->width % 2) == 1) {
        input->width--;
    }

    if( (input->height % 2) == 1) {
        input->height--;
    }
}


/*---------------------- DECOMPRESSION --------------------*/

/*
 Name: decompress40
 Parameters: A file pointer that points to the ppm image inputted by the 
 user
 Return: void
 Purpose: Decompresses the compressed image given on the input stream 
          and prints it on to standard output following ppm guidelines. 
          This function calls respective decompress image functions to 
          handle the decompression.
 */
extern void decompress40 (FILE *input) /* reads PPM, writes compressed image */
{ 
    assert(input != NULL);

    /*Read in given compressed ppm image file*/
    unsigned height, width;
    int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u", &width, &height);

    assert(read == 2);
    int c = getc(input);
    assert(c == '\n');
    assert(width > 0 && height > 0);

    A2Methods_T methods = uarray2_methods_plain;  
    assert(methods);
    
    /* 2D array that holds the codewords representing given compressed image */
    A2 words = methods->new(width/2, height/2, sizeof(uint32_t));

    /* Create instance of cv structs that hold A2 arrays and methods 
       for dct quantized, dctfloat, and component video
       representations, respectively. */
    cv dctQuantized = malloc(sizeof(struct cv));
    dctQuantized->methods = methods;
    dctQuantized->pixels = methods->new(width/2, height/2, sizeof(struct dctQ));

    cv dctFloat = malloc(sizeof(struct cv));
    dctFloat->methods = methods;
    dctFloat->pixels = methods->new(width/2, height/2, sizeof(struct dctF));

    cv cvImg = malloc(sizeof(struct cv));
    cvImg->methods = methods;
    cvImg->pixels = methods->new(width, height, sizeof(struct xyz)); 

    /* Creating the Pnm_ppm that will hold the decompressed image */
    A2 array = methods->new(width, height, sizeof(struct Pnm_rgb));
    Pnm_ppm outputImg = malloc(sizeof(struct Pnm_ppm));
    outputImg->width = width;
    outputImg->height = height;
    outputImg->denominator = SCALE; 
    outputImg->methods = methods;
    outputImg->pixels = array;

    /* Mapping functions that go through all the modules of image decompression, finally
       printing out the decompressed image to stdout */
    methods->map_row_major(words, readWord, input);
    methods->map_row_major(words, unpack, dctQuantized);
    methods->map_row_major(dctQuantized->pixels, unquantizeDCT, dctFloat);
    methods->map_row_major(dctFloat->pixels, dctToCV, cvImg);
    methods->map_row_major(cvImg->pixels, cvToRgb, outputImg);

    Pnm_ppmwrite(stdout, outputImg);
    
    /* freeing memory*/
    methods->free(&cvImg->pixels);
    free(cvImg);
    methods->free(&dctFloat->pixels);
    free(dctFloat);
    methods->free(&dctQuantized->pixels);
    free(dctQuantized);
    methods->free(&words);
    Pnm_ppmfree(&outputImg);
}


