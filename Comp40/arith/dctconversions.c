/******************************************************************************
 *                         dctconversions.c                                   *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation for our DCT          * 
                conversions that carries out discrete cosine transformations  *
                (dct) on component video representations (Y/Pb/Pr values)     *
                and the reverse transformations for decompression.            *
                Prepares the DCT values (a,b,c,d,avgPb,abgPr) by making sure  * 
                that they are within range (i.e. +0.3 and -0.3).              *
                                                                              *
 *****************************************************************************/
#include "dctconversions.h"

const float A_MAX = 1.0;
const float A_MIN = 0.0;
const float BCD_MAX = 0.3;
const float BCD_MIN = -0.3;
const float CHROMA_MAX = 0.5;
const float CHROMA_MIN = -0.5;


/*------------------------- COMPRESSION FUNCTIONS --------------------------*/


/*
 Name: cvToDCT 
 Parameters: apply function parameters as specified by the a2methods 
             file. Takes in a 2D Array that stores dctFloat pixels and a 
             closure arguement that stores pixels in component video
              representation (Y, Pb, Pr values).
 Return: void 
 Purpose: Converts each 2*2 block of component video pixels to dctFloats 
            using discrete cosine transformations. Checks the range of
            the dctFloats once they are converted to make sure they are 
            in between the max's and min's for the corresponding 
            luminance and chroma values.
 */
void cvToDCT(int col, int row, A2 dctFloat,
                A2Methods_Object *elem, void *cvImg)
{
    (void) dctFloat;
    cv input = (cv) cvImg;

    int col1 = 2 * col; 
    int col2 = 2 * col + 1;
    int row1 = 2 * row;
    int row2 = 2 * row + 1;
    /* grab 2*2 block of component video pixels*/
    xyz pix1 = input->methods->at(input->pixels, col1, row1);
    xyz pix2 = input->methods->at(input->pixels, col2, row1);
    xyz pix3 = input->methods->at(input->pixels, col1, row2);
    xyz pix4 = input->methods->at(input->pixels, col2, row2);

    /* convert component video representation to dct floats*/
    pixToDCT(pix1->Y, pix2->Y, pix3->Y, pix4->Y, (dctF)elem);
    ((dctF)elem)->avgPb = avgP(pix1->Pb, pix2->Pb, pix3->Pb, pix4->Pb);
    ((dctF)elem)->avgPr = avgP(pix1->Pr, pix2->Pr, pix3->Pr, pix4->Pr);
    
    /*check range of dctfloat values a,b,c,d,avgPb,avgPr*/
    checkRange((dctF)elem);
}

/*
 Name: avgP
 Parameters: 4 floats that represent either all Pr or Pb values
                in each 2*2 block of component video pixels.
 Return: the average chroma (Pb/Pr) value of the 4 pixels
 Purpose: Computes the average chroma value of each 2*2 block 
 */
float avgP(float p1, float p2, float p3, float p4)
{
    float avgP = (p1 + p2 + p3 + p4) / 4.0;
    return avgP;
}

/*
 Name: pixToDCT 
 Parameters: 4 floats that represent the luminance
            values in each 2*2 block of component video pixels.
 Return: void 
 Purpose: Carries out the mathematical computation for the
             luminance values a,b,c,d
 */
void pixToDCT(float y1, float y2, float y3, float y4, dctF elem)
{
    elem->a = (y4 + y3 + y2 + y1) / 4.0;
    elem->b = (y4 + y3 - y2 - y1) / 4.0;
    elem->c = (y4 - y3 + y2 - y1) / 4.0;
    elem->d = (y4 - y3 - y2 + y1) / 4.0;
}


/*------------------------ DECOMPRESSION FUNCTIONS -------------------------*/

/*
 Name: cvToDCT 
 Parameters: apply function parameters as specified by the a2methods 
            file. Takes in a 2D Array that stores dctFloat pixels and a 
            closure arguement that stores pixels in component video
            representation. 
 Return: void 
 Purpose: Converts each dctFloat pixel into 4 component video pixels. 
            Checks the range of each dctFloats before conversion to make 
            sure they are in between the max's and min's of luminance and 
            chroma values.
 */
void dctToCV(int col, int row, A2 dctFloat,
                A2Methods_Object *elem, void *cvImg) 
{
    (void) dctFloat;
    cv input = (cv) cvImg;

    int col1 = 2 * col;
    int col2 = 2 * col + 1;
    int row1 = 2 * row;
    int row2 = 2 * row + 1;

    /* checking range of dctfloat values a,b,c,d,avgPb, avgPr.*/
    checkRange((dctF)elem);

    /*converting each dctfloat to 4 component video pixels (Y, Pb, Pr)*/
    dctToPix(input->methods->at(input->pixels, col1, row1), 
                input->methods->at(input->pixels, col2, row1),
                input->methods->at(input->pixels, col1, row2),
                input->methods->at(input->pixels, col2, row2),
                (dctF)elem);
}

/*
 Name: dctToPix
 Parameters: 4 xyz struct holding a component video pixel with 
                Y, Pb, Pr values 
 Return: void 
 Purpose: Carries out the mathematical computation to convert 
            dctFloats back to component video representation
 */
void dctToPix( xyz pix1 , xyz pix2, xyz pix3, xyz pix4, dctF elem)
{
    pix1->Y = elem->a - elem->b - elem->c + elem->d;
    pix1->Pb = elem->avgPb;
    pix1->Pr = elem->avgPr;

    pix2->Y = elem->a - elem->b + elem->c - elem->d;
    pix2->Pb = elem->avgPb;
    pix2->Pr = elem->avgPr;

    pix3->Y = elem->a + elem->b - elem->c - elem->d;
    pix3->Pb = elem->avgPb;
    pix3->Pr = elem->avgPr;

    pix4->Y = elem->a + elem->b + elem->c + elem->d;
    pix4->Pb = elem->avgPb;
    pix4->Pr = elem->avgPr;
}

/*--------------------------- HELPER FUNCTIONS -----------------------------*/

/*
 Name: checkRange
 Parameters: a dctF struct holding a pixel in dctFloat representation 
            (a,b,c,d,avgPb,avgPr values)
 Return: void 
 Purpose: Checks the range of each dct value to make sure they are all 
            within the specified maximum and minimum's. 
 */
void checkRange(dctF elem)
{
    elem->a = rangeHelper(elem->a, A_MAX, A_MIN);
    elem->b = rangeHelper(elem->b, BCD_MAX, BCD_MIN);
    elem->c = rangeHelper(elem->c, BCD_MAX, BCD_MIN);
    elem->d = rangeHelper(elem->d, BCD_MAX, BCD_MIN);

    elem->avgPb = rangeHelper(elem->avgPb, CHROMA_MAX, CHROMA_MIN);
    elem->avgPr = rangeHelper(elem->avgPr, CHROMA_MAX, CHROMA_MIN);
}

/*
 Name: checkRangeHelper
 Parameters: a float, the max value the float can be, and the min
            value the float can be. 
 Return: a float that's been put into the range specified
 Purpose: A helper function that specifically carries out the
            process of scaling a value of the dctFloat pixel. This
            function is called by check_range for each specific 
            value of the pixel (i.e. a, b, c, d, avgPb, or avgPr) 
 */
float rangeHelper(float x, float MAX, float MIN)
{
    if (x > MAX) {
        return MAX;
    } else if (x < MIN) {
        return MIN;
    } else {
        return x;
    }
}