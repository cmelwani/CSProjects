/**************************************************************
 *
 *                     memory.c
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Holds the implementation of the memory
 *     interface and creates the memory struct. Implements
 *     segmentedLoad, segmentedStore, mapSegment, unmapSegment
 *     instructions 
 *
 **************************************************************/

#include "memory.h"

/* 
 * Name: memNew()
 * Description: Takes in the segment with instruction words and 
 *              creates a new memory struct where the instruction segment 
 *              is set to segment 0 in the sequence of segments. A new 
 *              sequence is created for segments and a sequence is created 
 *              to hold unmapped ID's. Returns the new memory struct. 
 * Expectations: The segment passed through to the function is not null
*/
mem memNew(Seq_T segment_0) 
{
    mem new_mem = malloc(sizeof(struct mem));
    assert(new_mem != NULL);
    assert(segment_0 != NULL);

    new_mem->segments = Seq_new(0);
    Seq_addlo(new_mem->segments, segment_0);
    // new_mem->unmapped = Stack_new();
    new_mem->unmapped = Seq_new(0);
    return new_mem;
}

/* 
 * Name: memFree()
 * Description: Frees the memory struct and all of the contents in there. 
 * Expectations: memory struct is non-null. 
*/
void memFree(mem new_mem) 
{
    assert(new_mem != NULL);

    for(int i = 0; i < Seq_length(new_mem->segments); i++) {
        Seq_T to_free = Seq_get(new_mem->segments, i);
        Seq_free(&to_free);
    }

    Seq_free(&(new_mem->segments));
    Seq_free(&(new_mem->unmapped));
    free(new_mem);
}

/* 
 * Name: segmentedLoad()
 * Description: Load the value at new_mem->segments[rb][rc]
 * Expectations: memory struct is non-null
*/
uint32_t segmentedLoad(mem new_mem, uint32_t rb, uint32_t rc)
{
	assert(new_mem != NULL);
    Seq_T segment_b = Seq_get(new_mem->segments, rb);
    assert(segment_b != NULL);
    uint32_t word = (uint32_t) (uintptr_t) Seq_get(segment_b, rc);
    return word;
}

/* 
 * Name: segmentedStore()
 * Description: Store rc in the location new_mem->segments[ra][rb]
 * Expectations: memory struct is non-null. 
*/
void segmentedStore(mem new_mem, uint32_t ra, uint32_t rb, uint32_t rc) 
{
    assert(new_mem != NULL);
    Seq_T segment_a = Seq_get(new_mem->segments, ra);
    Seq_put(segment_a, rb, (void*) (uintptr_t) rc);
}

/* 
 * Name: mapSegment()
 * Description: Initializes a new segment sequence, populating its
 *              length provided in rc with 0s. Then checks to see
 *              if there are unmapped segments available to
 *              populate. If there are, pop the identifier off and
 *              use it in segments. If not, add to the end of the
 *              mapped segments sequence.
 * Expectations: memory struct is non-null. 
*/
uint32_t mapSegment(mem new_mem, uint32_t rc)
{
    assert(new_mem != NULL);
    assert((Seq_length(new_mem->segments) + 1) < 4294967296);
    Seq_T new_seg = Seq_new(rc);
    	for (int i = 0; i < (int)rc; i++) {
	      Seq_addhi(new_seg, (void*) (uintptr_t) 0);
        }
    uint32_t id;
    if(Seq_length(new_mem->unmapped) != 0) {
        id = (uint32_t) (uintptr_t) Seq_remhi(new_mem->unmapped);
        Seq_T old_sequence = Seq_put(new_mem->segments, id, (void*) new_seg);
        Seq_free(&old_sequence);
    } else {
        Seq_addhi(new_mem->segments, (void*) new_seg);
        id = Seq_length(new_mem->segments) - 1;
    }
    return id;
}

/* 
 * Name: unmapSegment
 * Description: Takes an identifier for a segment to be unmapped.
 *              Pushes it onto the unmapped sequence.
 * Expectations: memory struct is non-null
*/
void unmapSegment(mem new_mem, uint32_t rc)
{
    assert(new_mem != NULL);    
    Seq_addhi(new_mem->unmapped, (void*) (uintptr_t) rc);
}