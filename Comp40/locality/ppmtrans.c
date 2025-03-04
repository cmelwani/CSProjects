/*
 *                      ppmtrans.c
 *
 *         This program rotates an image file given by a user
 *         either 0, 90, 180, or 270 depending on what the user
 *         specifies.
 *         
 *         Command line: 
 *         ppmtrans.c [[-rotate <angle>] [-{row,col,block}-major] [filename]]
 *         If no filename is supplied, the image is read from stdin.
 *
 *         Author: Cheryl Melwani and Devan Venkataraman
 *         Date: March 8th 2021
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "mem.h"
#include "cputiming.h"

#define SET_METHODS(METHODS, MAP, WHAT) do {                \
    methods = (METHODS);                                    \
    assert(methods != NULL);                                \
    map = methods->MAP;                                     \
    if (map == NULL) {                                      \
            fprintf(stderr, "%s does not support "          \
                            WHAT "mapping\n",               \
                            argv[0]);                       \
            exit(1);                                        \
    }                                                       \
} while (0)

static void
usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [-rotate <angle>] "
                    "[-{row,col,block}-major] [filename]\n",
                    progname);
    exit(1);
}

void closeFile(FILE *inputFile);
void rotate_0(int i, int j, A2Methods_UArray2 array2,
                                A2Methods_Object *ptr, void *cl);
void rotate_90(int i, int j, A2Methods_UArray2 array2,
                                A2Methods_Object *ptr, void *cl);
void rotate_180(int i, int j, A2Methods_UArray2 array2,
                                A2Methods_Object *ptr, void *cl);
void rotate_270(int i, int j, A2Methods_UArray2 array2, 
                                A2Methods_Object *ptr, void *cl);
double perform_trans(Pnm_ppm image, int rotation, A2Methods_T methods, 
                                A2Methods_mapfun *map);

void record_time(char *time_file_name, double time_taken,
                 Pnm_ppm image, int rotation, char *map_method);


int main(int argc, char *argv[]) 
{
    char *time_file_name = NULL;
    char *map_used = "row-major";
    (void) time_file_name;
    int   rotation       = 0;
    int   i;

    /* default to UArray2 methods */
    A2Methods_T methods = uarray2_methods_plain; 
    assert(methods);

    /* default to best map */
    A2Methods_mapfun *map = methods->map_default; 
    assert(map);

    FILE *fp = stdin;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-row-major") == 0) {
            map_used = "row-major";
            SET_METHODS(uarray2_methods_plain, map_row_major, 
                        "row-major");
        } else if (strcmp(argv[i], "-col-major") == 0) {
            map_used = "column-major";
            SET_METHODS(uarray2_methods_plain, map_col_major, 
                        "column-major");
        } else if (strcmp(argv[i], "-block-major") == 0) {
            map_used = "block-major";
            SET_METHODS(uarray2_methods_blocked, map_block_major,
                        "block-major");
        } else if (strcmp(argv[i], "-rotate") == 0) {
            if (!(i + 1 < argc)) {      /* no rotate value */
                usage(argv[0]);
            }
            char *endptr;
            rotation = strtol(argv[++i], &endptr, 10);
            if (!(rotation == 0 || rotation == 90 ||
                rotation == 180 || rotation == 270)) {
                fprintf(stderr, 
                        "Rotation must be 0, 90 180 or 270\n");
                usage(argv[0]);
            }
            if (!(*endptr == '\0')) {    /* Not a number */
                    usage(argv[0]);
            }
        } else if (strcmp(argv[i], "-time") == 0) {
            time_file_name = argv[++i];
        } else if (*argv[i] == '-') {
            fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                    argv[i]);
            usage(argv[0]);
        } else if (argc - i > 1) {
            fprintf(stderr, "Too many arguments\n");
            usage(argv[0]);
        } else {
            fp = fopen(argv[i], "rb");
            assert(fp != NULL);
            break;
        }
    }

    Pnm_ppm image = Pnm_ppmread(fp, methods);
    closeFile(fp);

    double time_taken = perform_trans(image, rotation, methods, map);
    
    if (time_file_name != NULL) {
        record_time(time_file_name, time_taken, image, rotation, map_used);
    }

    Pnm_ppmfree(&image);

    return 0;
}

 /* Purpose: Handles closing the file that was earlier opened for reading */
void closeFile(FILE *inputFile) 
{
    if (inputFile != stdin) {
        assert(fclose(inputFile) == 0);
    }
}

 /* Purpose: Apply function that handles the 0 rotation of image */
void rotate_0(int i, int j, A2Methods_UArray2 array2,
                                A2Methods_Object *ptr, void *cl)
{
    (void) array2;
    Pnm_ppm *copy = cl;
    Pnm_rgb new_pixel = (*copy)->methods->at((*copy)->pixels, i, j);
    *new_pixel = *(Pnm_rgb) ptr;
}

 /* Purpose: Apply function that handles the 90 rotation of image */
void rotate_90(int i, int j, A2Methods_UArray2 array2,
                                A2Methods_Object *ptr, void *cl) {

    Pnm_ppm *copy = cl;
    int h = (*copy)->methods->height(array2);
    Pnm_rgb new_pixel = (*copy)->methods->at((*copy)->pixels, h - j - 1, i);
    *new_pixel = *(Pnm_rgb) ptr;
}

 /* Purpose: Apply function that handles the 180 rotation of image */
void rotate_180(int i, int j, A2Methods_UArray2 array2, 
                                A2Methods_Object *ptr, void *cl) {
    Pnm_ppm *copy = cl;
    int h = (*copy)->methods->height(array2);
    int w = (*copy)->methods->width(array2);
    Pnm_rgb new_pixel = (*copy)->methods->at((*copy)->pixels, 
                                                w - i - 1, h - j - 1);
    *new_pixel = *(Pnm_rgb) ptr;
}

 /* Purpose: Apply function that handles the 270 rotation of image */
void rotate_270(int i, int j, A2Methods_UArray2 array2, 
                                A2Methods_Object *ptr, void *cl) {
    Pnm_ppm *copy = cl;
    int w = (*copy)->methods->width(array2);
    Pnm_rgb new_pixel = (*copy)->methods->at((*copy)->pixels, j, w - i - 1);
    *new_pixel = *(Pnm_rgb) ptr;
}

 /* Purpose: Handles calling respective map and apply functions depending on 
    the rotation specified by the user. CPUTime is calculated and returned
    in this function.
    Expected output: CPU time of the rotation  */
double perform_trans(Pnm_ppm image, int rotation, A2Methods_T methods, 
                        A2Methods_mapfun *map)
{
    Pnm_ppm copy_image;
    NEW(copy_image);

    CPUTime_T timer = CPUTime_New();
    CPUTime_Start(timer);
        
    if (rotation == 0) {
        A2Methods_UArray2 array2 = methods->new(image->width, 
                               image->height, methods->size(image->pixels));
        copy_image->pixels = array2;
        copy_image->methods = methods;
        copy_image->width = image->width;
        copy_image->height = image->height;
        copy_image->denominator = image->denominator;

        map(image->pixels, rotate_0, &copy_image);
    }
    if (rotation == 90) {
        /* Initializing 2d array with the correct (flipped) dimensions */
        A2Methods_UArray2 array2 = methods->new(image->height, 
                                image->width, methods->size(image->pixels));
        copy_image->pixels = array2;
        copy_image->methods = methods;
        copy_image->width = image->height;
        copy_image->height = image->width;
        copy_image->denominator = image->denominator;

        map(image->pixels, rotate_90, &copy_image);
    }
    else if (rotation == 180) {
        A2Methods_UArray2 array2 = methods->new(image->width, 
                                image->height, methods->size(image->pixels));
        copy_image->pixels = array2;
        copy_image->methods = methods;
        copy_image->width = image->width;
        copy_image->height = image->height;
        copy_image->denominator = image->denominator;

        map(image->pixels, rotate_180, &copy_image);
    }
    else if (rotation == 270) {
        /* Initializing 2d array with the correct (flipped) dimensions */
        A2Methods_UArray2 array2 = methods->new(image->height, 
                                image->width, methods->size(image->pixels));
        copy_image->pixels = array2;
        copy_image->methods = methods;
        copy_image->width = image->height;
        copy_image->height = image->width;
        copy_image->denominator = image->denominator;
        
        map(image->pixels, rotate_270, &copy_image);
    }

    double time_taken = CPUTime_Stop(timer);
    CPUTime_Free(&timer);

    Pnm_ppmwrite(stdout, copy_image);
    Pnm_ppmfree(&copy_image);

    return time_taken;
}

 /* Purpose: Printing timing data to the output file given by the user */
void record_time(char *time_file_name, double time_taken,
                 Pnm_ppm image, int rotation, char *map_method) {
    FILE *fp;
    fp = fopen(time_file_name, "a");
    assert(fp != NULL);

    double num_pixels = image->width * image->height;
    double average_time = time_taken / num_pixels;
    fprintf(fp, "-------------------TIMING DATA----------------------\n");
    fprintf(fp, "Rotation performed: %i degrees\n", rotation);
    fprintf(fp, "Mapping method used: %s \n", map_method);
    fprintf(fp, "Original image width: %i pixels\n", image->width);
    fprintf(fp, "Original image height: %i pixels\n", image->height);
    fprintf(fp, "Number of pixels: %.0f pixels\n", num_pixels);
    fprintf(fp, "Total time taken: %.0f nanoseconds\n", time_taken);
    fprintf(fp, "Average time taken per input pixel: %.0f nanoseconds\n", 
            average_time);
    fclose(fp);
}