/******************************************************************************
 *                            cvconversions.c                                 *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation for the 2 way        * 
                conversions between RGB and component video representation.   * 
                Conducts the necessary math and handles scaling of RGB values * 
                                                                              *
 *****************************************************************************/
#include "cvconversions.h"

const float RGB_MAX = 255.0;
const float RGB_MIN = 0.0;


/*------------- COMPRESSION FUNCTIONS --------------*/

/*
 Name: rgbToCv 
 Parameters: apply function parameters as specified by the a2methods 
            file. Takes in a 2D Array that holds component video
            pixels (Y,Pb,Pr values) and a closure arguement that is
            a non-compressed Pnm_ppm image inputted by the user.
 Return: void 
 Purpose: Converts all pixels in the input img from RGB to XYZ component
            video representation.
 */
void rgbToCv(int i, int j, A2 cvImg,
                A2Methods_Object *elem, void *inputImg)
{
    (void)cvImg;
    Pnm_ppm input = (Pnm_ppm)inputImg;
    Pnm_rgb currPix = input->methods->at(input->pixels, i, j);
    
    int d = input->denominator;
    cvCalc((float) currPix->red / d , (float) currPix->green / d, 
            (float) currPix->blue / d , (xyz) elem);
}

/*
 Name: cvCalc 
 Parameters: rgb float values and the current component video 
                pixel that's being populated
 Return: void 
 Purpose: Carries out the mathematical computations of converting 
            red, green and blue values into Y, Pb and Pr values. 
 */
void cvCalc(float r, float g, float b, xyz elem)
{
    elem->Y  = 0.299     * r + 0.587    * g + 0.114    * b;
    elem->Pb = -0.168736 * r - 0.331264 * g + 0.5      * b;
    elem->Pr = 0.5       * r - 0.418688 * g - 0.081312 * b;
}

/*------------- DECOMPRESSION FUNCTIONS --------------*/


/*
 Name: cvToRgb 
 Parameters:  apply function parameters as specified by the a2methods 
                file. Takes in a 2D Array that holds component video
                pixels and a closure arguement that is the compressed 
                Pnm_ppm image inputted by the user.
 Return: void 
 Purpose: Converts all pixels in the image from component video 
            representation to rgb representation.
 */
void cvToRgb(int i, int j, A2 cvImg,
                A2Methods_Object *elem, void *outputImg)
{
    (void) cvImg;
    Pnm_ppm output = (Pnm_ppm) outputImg;
    Pnm_rgb currPix = output->methods->at(output->pixels, i, j);
    
    rgbCalc(((xyz)elem)->Y * RGB_MAX, ((xyz)elem)->Pb * RGB_MAX, 
            ((xyz)elem)->Pr * RGB_MAX, (Pnm_rgb) currPix);
    
}

/*
 Name: rgbCalc
 Parameters: XYZ component video float values (Y, Pb, Pr)and the 
            current rgb pixel that's being populated
 Return: void 
 Purpose: Carries out the mathematical computation of converting 
            component Y, Pb, and Pr values into red green and blue  
 */
void rgbCalc(float Y, float Pb, float Pr, Pnm_rgb currPix) 
{
    float r = 1.0 * Y + 0.0      * Pb + 1.402    * Pr;
    float g = 1.0 * Y - 0.344136 * Pb - 0.714136 * Pr; 
    float b = 1.0 * Y + 1.722    * Pb + 0.0      * Pr;

    currPix->red = round(scaleRGB(r));
    currPix->green = round(scaleRGB(g));
    currPix->blue = round(scaleRGB(b));
} 

/*
 Name: scaleRGB
 Parameters: a float that represents either a red, green, or
                 blue rgb value. 
 Return: the scaled float rgb value
 Purpose: Scales the float value in order to make sure its in
             between RGB_MIN AND RGB_MAX 
 */
float scaleRGB(float rgb) {

    if(rgb > RGB_MAX) {
        rgb = RGB_MAX;
    } else if (rgb < RGB_MIN) {
        rgb = RGB_MIN;
    }
    return rgb;
}


