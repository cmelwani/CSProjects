/****************************************************************************
 *                            bitpack.c                                     *
 *                                                                          *
 * Authors:    Anna Wang (awang15), Cheryl Melwani (cmelwa01)               *
 * Date:       March, 2020                                                  *
 * Course:     Comp 40                                                      *
 * Assignment: Arith                                                        *
 *                                                                          *
 * Description: This file holds the implementation of the bitpack interface *
 *              that handles creating new codewords that can be packed,     *
 *              packing the codewords, and getting values from the packed   *
 *              codewords.                                                  *
 *                                                                          *
 ***************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "except.h"
#include "bitpack.h"

const unsigned MAX_WIDTH   = 64;
const int      LEFT  = 0;
const int      RIGHT = 1;

uint64_t uShift(int direction, uint64_t value, unsigned shift);
int64_t sShift(int direction, int64_t value, unsigned shift);

Except_T Bitpack_Overflow = { "Overflow packing bits" };
/*
 Name: Bitpack_newu
 Parameters: 4 unsigned integers representing the original word, value 
            indicating the width, location of the field's least 
            significant bit and unsigned value to be added to the word.
 Return: 64 bit unsigned integer representing a new word
 Purpose: Replaces the field of width with its least significant 
            bit at location lsb replaced by a width-bit representation 
            of value. Modifies original word from lsb to lsb+width. 
 */
uint64_t Bitpack_newu(uint64_t word, unsigned width, 
                        unsigned lsb, uint64_t value)
{
    assert(width <= MAX_WIDTH);
    assert(lsb + width <= MAX_WIDTH);

    if(!Bitpack_fitsu(value, width)) {
        RAISE(Bitpack_Overflow);
    }

    //negate mask in order to zero out the desired field
    uint64_t mask = ~0;
    mask = uShift(RIGHT, mask, MAX_WIDTH - width);
    mask = uShift(LEFT, mask, lsb);
    
    //clear the desired field 
    word = word & ~mask;
    //left shift new value so it matches the same points as the mask
    value = uShift(LEFT, value, lsb);
    //or the word and the new value to get the new packed word 
    word = word | value;
    return word;
}


/*
 Name: Bitpack_news
 Parameters: 4 integers representing the original word, 
            value indicating the width, location of the 
            field's least significant bit and the signed 
            value to be added to the word.
 Return: 64 bit unsigned integer representing a new word
 Purpose: Replaces the field of width with its least
            significant bit at location lsb replaced by a 
            width-bit representation of value. Modifies 
            original word from lsb to lsb+width. 
 */
uint64_t Bitpack_news(uint64_t word, unsigned width, 
                        unsigned lsb, int64_t value)
{
    assert(width <= MAX_WIDTH);
    assert(lsb + width <= MAX_WIDTH);

    if(!Bitpack_fitss(value, width)) {
        RAISE(Bitpack_Overflow);
    }

    //mask removes leading ones if the signed value is negative
    uint64_t mask = ~0;
    mask = uShift(RIGHT, mask, MAX_WIDTH - width);
    value = value & mask;
    word = Bitpack_newu(word, width, lsb, (uint64_t) value);
    return word;
    
}

/*
 Name: Bitpack_fitsu
 Parameters: 2 unsigned integers (64 bit width) holding a value to be
            to be represented and value indicating the 
            bits available
 Return: boolean (T/F)
 Purpose: Tests if an integer can be represented in width bits. 
         Return true if the given unsigned 64 bits integer can be 
            represented in width-bits, else return false. 
 */
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
    assert(width <= MAX_WIDTH);

    uint64_t boundary;

    if(width == MAX_WIDTH) {
        boundary = UINT64_MAX;
    } else {
        boundary = uShift(LEFT, 1, width) - 1;
    }

    if(n > boundary || width == 0) {
        return false;
    } else {
        return true;
    }
}

/*
 Name: Bitpack_fitss
 Parameters: signed 64bit integer to be represented and unsigned 
            value indicating the bits available
 Return: boolean (T/F)
 Purpose: Tests if an integer can be represented in width bits. 
            Return true if the given signed 64 bits integer can 
            be represented in width-bits, else return false. 
 */
bool Bitpack_fitss(int64_t n, unsigned width)
{
    assert(width <= MAX_WIDTH);
    int64_t highBound = sShift(LEFT, 1, width - 1) - 1;
    int64_t lowBound = sShift(LEFT, 1, width - 1) * -1;

    if( (lowBound > n || n > highBound) || width == 0 ) {
        return false;
    }
    return true;
}

/*
 Name: Bitpack_getu
 Parameters: 3 unsigned integers that represent the given word, 
            width of the field, and location of the field's least
             significant bit 
 Return: unsigned 64bit integer
 Purpose: Extracts an unsigned 64 bit integer from a word given 
            the width of the field using a mask. */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width <= MAX_WIDTH);
    assert(width + lsb <= MAX_WIDTH);

    if (width == 0) {
        return 0;
    }

    uint64_t mask = ~0;
    mask = uShift(RIGHT, mask, MAX_WIDTH - width);
    mask = uShift(LEFT, mask, lsb);

    uint64_t field = uShift(RIGHT, word & mask, lsb);
    return field;
}


/*
 Name: Bitpack_gets
 Parameters: 3 unsigned integers that represent the given 
              word, width of the field, and location of the 
              field's least significant bit 
 Return: signed 64bit integer
 Purpose: Extracts a signed 64 bit integer from a word 
              given the width of the field using a mask. */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width <= MAX_WIDTH);
    assert(width + lsb <= MAX_WIDTH);

    if (width == 0) {
        return 0;
    }

    int64_t value = Bitpack_getu(word, width, lsb);
    value = sShift(LEFT, value, MAX_WIDTH - width);
    value = sShift(RIGHT, value, MAX_WIDTH - width);
    return value;

}


/*----------------------- HELPER FUNCTIONS -----------------------*/

/*
 Name: uShift
 Parameters: direction of shift, unsigned value to be shifted, 
            and the amount to shift unsigned value by
 Return: unsigned 64 bit integer
 Purpose: If possible (shift < MAX_WIDTH), shifts given unsigned
        64 bit integer by shift value in the specified direction.
 */
uint64_t uShift(int direction, uint64_t value, unsigned shift)
{
    if(shift == MAX_WIDTH) {
        /* if we shift all the way right or left,
             value becomes 0 */
        return 0;
    } else {
        if(direction == LEFT){
            return value << shift;
        } else {
            return value >> shift;
        }
    }
}

/*
 Name: sShift
 Parameters: direction of shift, signed value to be shifted, and 
            the amount to shift signed value by
 Return: signed 64 bit integer
 Purpose: If possible (shift < MAX_WIDTH), shifts given signed
        64 bit integer by shift value in the specified direction.
 */
int64_t sShift(int direction, int64_t value, unsigned shift)
{
    if(shift == MAX_WIDTH) {
        if(direction == LEFT) {
        /*if we shift all the way to the left, value becomes 0 */
            return 0;
        } else {
        /* If we shift to the right, by two's complement value
            becomes -1 */
            return -1;
        } 
    } else {
        if(direction == LEFT) {
            return value << shift;
        } else {
            return value >> shift;
        }
    }
}

