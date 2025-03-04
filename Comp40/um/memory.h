/**************************************************************
 *
 *                     memory.h
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Holds the memory struct interface and the 
 *     function declarations for segmentedLoad, 
 *     segmentedStore, mapSegment, unmapSegment
 *     instructions 
 *
 **************************************************************/

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "seq.h"
#include "stack.h"
#include "assert.h"

typedef struct mem {
    Seq_T segments;
    Seq_T unmapped; 
} *mem;

mem memNew(Seq_T instructions);
void memFree(mem new_mem);
uint32_t segmentedLoad(mem new_mem, uint32_t b, uint32_t c);
void segmentedStore(mem new_mem, uint32_t a, uint32_t b, uint32_t c);
uint32_t mapSegment(mem new_mem, uint32_t c);
void unmapSegment(mem new_mem, uint32_t c);

#endif



