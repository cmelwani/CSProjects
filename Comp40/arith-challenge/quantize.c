/******************************************************************************
 *                            quantize.c                                      *
 *                                                                            *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)                 *
 * Date:       March, 2020                                                    *
 * Course:     Comp 40                                                        *
 * Assignment: arith                                                          *
 *                                                                            *
 * Description: This program contains the implementation responsible for the  *
                 quantization of DCT floating point values into signed and    *
                 unsigned integers, and the inverse conversions.              * 
                                                                              *
 *****************************************************************************/
#include "quantize.h"

/*------------------------- COMPRESSION FUNCTIONS --------------------------*/

/*
 Name: quantizeDCT 
 Parameters: apply function parameters as specified by the a2methods 
              file. Applied onto a 2D Array that stores dctQuantized pixels 
              and a closure argument that is a 2D Array that stores dctFloat 
              values.
 Return: void 
 Purpose: Carries out the conversion from dct floating point values 
          into quantized vlaues (aka signed and unsigned integers). 
 */
void quantizeDCT(int i, int j, A2 dctQuantized,
                A2Methods_Object *elem, void *dctFloat)
{
    (void)dctQuantized;
    cv input = (cv) dctFloat;

    dctF currPix = input->methods->at(input->pixels, i, j);

    ((dctQ)elem)->a = quantizeA(currPix->a);
    ((dctQ)elem)->b = quantizeBCD(currPix->b);
    ((dctQ)elem)->c = quantizeBCD(currPix->c);
    ((dctQ)elem)->d = quantizeBCD(currPix->d);
    
    ((dctQ)elem)->avgPb = Arith40_index_of_chroma(currPix->avgPb);
    ((dctQ)elem)->avgPr = Arith40_index_of_chroma(currPix->avgPr);

}

/*
 Name: quantizeA
 Parameters: floating point number that is the 'a' component of the 
             dct value.
 Return: the unsigned quantized value of 'a'
 Purpose: Carries out the mathematical computation to convert 'a'
            from floating point value to an unsigned integer.
 */
unsigned quantizeA(float x) 
{
    unsigned y = x * 63;
    return y;
}

/*
 Name: quantizeBCD
 Parameters: floating point number that is either the 
                b, c, or d component of the dct float.
 Return: the unsigned quantized value of either b,c, or d
 Purpose: Carries out the mathematical computation to convert b,c,d
            from a floating point value to a signed integer.
 */
signed quantizeBCD(float x) 
{
    return x * 103;
}

/*----------------------- DECOMPRESSION FUNCTIONS --------------------------*/

/*
 Name: unquantizeDCT 
 Parameters: apply function parameters as specified by the a2methods 
              file. Applied onto a 2D Array that stores dctQuantized pixels 
              and a closure argument that is a 2D Array that stores dctFloat 
              values.
 Return: void 
 Purpose: Carries out the conversion from dct quantized values 
          (signed and unsigned integers) to dct floating point values. 
 */
void unquantizeDCT(int i, int j, A2 dctQuantized,
                A2Methods_Object *elem, void *dctFloat)
{
    (void)dctQuantized;
    cv output = (cv) dctFloat;

    dctF currPix = output->methods->at(output->pixels, i, j);
    
    currPix->a = unquantizeA(((dctQ)elem)->a);
    currPix->b = unquantizeBCD(((dctQ)elem)->b);
    currPix->c = unquantizeBCD(((dctQ)elem)->c);
    currPix->d = unquantizeBCD(((dctQ)elem)->d);
    
    currPix->avgPb = Arith40_chroma_of_index(((dctQ)elem)->avgPb);
    currPix->avgPr = Arith40_chroma_of_index(((dctQ)elem)->avgPr);

}

/*
 Name: unquantizeA
 Parameters: unsigned integer that is the quantized a value  
             as part of the dct values.
 Return: the floating point value of 'a'
 Purpose: Carries out the mathematical computation to convert 'a'
            from an unsigned integer to a floating point value.
 */
float unquantizeA(unsigned x) 
{
    float y = (float)(x / 63.0);
    return y;
}

/*
 Name: unquantizeBCD
 Parameters: signed integer that is either the quantized
                b, c, or d values. (part of dct values)
 Return: the unsigned quantized value of either b,c, or d
 Purpose: Carries out the mathematical computation to convert b,c,d
            from a floating point value to a signed integer.
 */
float unquantizeBCD(signed x) 
{
    assert(x < 32 && x > -32);
    float y = (float)(x / 103.0);
    return y;
}
