/**************************************************************
 *
 *                     um.c
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/27/2021
 *
 *     Purpose: Handles the entire implementation of the 
 *              universal machine where all previous modules
 *              from hw6 are combined into one file. 
 *              
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "bitpack.h"

typedef struct Seg_T {
        int length;
        int size;
        uint32_t *array;
} *Seg_T;

typedef struct Seq_T {
        int length;
        int size;
        Seg_T *array; 
} *Seq_T;

typedef struct mem {
    Seq_T segments;
    Seg_T unmapped; 
} *mem;


extern Seg_T Seg_new(int hint);
extern void Seg_free(Seg_T seg);
extern int Seg_length(Seg_T seg);
extern uint32_t Seg_get(Seg_T seg, int i);
extern uint32_t Seg_put(Seg_T seg, int i, uint32_t val);
extern void Seg_addhi(Seg_T seg, uint32_t val);
extern uint32_t Seg_remhi(Seg_T seg);

extern Seq_T Seq_new(int hint);
extern void Seq_free(Seq_T seq);
extern int Seq_length(Seq_T seq);
extern Seg_T Seq_get(Seq_T seq, int i);
extern Seg_T Seq_put(Seq_T seq, int i, Seg_T seg);
extern void Seq_addhi(Seq_T seq, Seg_T seg);

mem memNew(Seg_T instructions);
void memFree(mem new_mem);
uint32_t segmentedLoad(mem new_mem, uint32_t b, uint32_t c);
void segmentedStore(mem new_mem, uint32_t a, uint32_t b, uint32_t c);
uint32_t mapSegment(mem new_mem, uint32_t c);
void unmapSegment(mem new_mem, uint32_t c);

Seg_T load_um(FILE* fp);
uint32_t getInstruction(FILE *fp, int byte1);

void executeInstr(Seg_T instructions);
void readinstr(uint32_t instruction);
void executeHelper(mem new_mem, uint32_t opcode, uint32_t a, uint32_t b, 
uint32_t c);

int main(int argc, char *argv[]) 
{
    if(argc != 2) {
        exit(EXIT_FAILURE);
    }

	FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "%s: No such file or directory\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Seg_T segment_0 = load_um(fp);

    fclose(fp);

    executeInstr(segment_0);
    exit(0);
}

/**************************************************************
 *                     um_loader.c
 **************************************************************/

/* 
 * Name: load_um()
 * Description: Calculates the number of instructions that the
 *              file holds and instantiates a sequence to
 *              store the instructions in memory.
 * Expectations: The number of bytes in the file is divisible
 *               by 4, aka only complete 32-bit instructions.
*/
Seg_T load_um(FILE* fp) {

    /* Calculate the number of bytes of the instructions */
    fseek(fp, 0L, SEEK_END);
    long int length = ftell(fp);

    if (length == 0 || length % 4 != 0) {
        exit(EXIT_FAILURE);
    }

    rewind(fp);

    /* Create a sequence to hold the 32 bit instruction codes */
    Seg_T segment_0 = Seg_new(length/4);

    int byte1;
    while ((byte1 = getc(fp)) != EOF) {
        Seg_addhi(segment_0, getInstruction(fp, byte1));
    }
    return segment_0;
}

/* 
 * Name: getInstruction()
 * Description: Gets 4 bytes from the instruction file and 
 *              packs it into a 32 bit intsr_code. Returns
 *              instr_code.
 * Expectations: none
*/
uint32_t getInstruction(FILE *fp, int byte1) {
    uint64_t instr_code = 0;
    byte1 = byte1 << 24;
    int byte2 = getc(fp) << 16;
    int byte3 = getc(fp) << 8;
    int byte4 = getc(fp);

    return (uint32_t) instr_code + byte1 + byte2 + byte3 + byte4;
}

/**************************************************************
 *                     memory.c
 **************************************************************/

/* 
 * Name: memNew()
 * Description: Takes in the segment with instruction words and 
 *              creates a new memory struct where the instruction segment 
 *              is set to segment 0 in the sequence of segments. A new 
 *              sequence is created for segments and a sequence is created 
 *              to hold unmapped ID's. Returns the new memory struct. 
 * Expectations: The segment passed through to the function is not null
*/
mem memNew(Seg_T segment_0) 
{
    mem new_mem = malloc(sizeof(struct mem));
    assert(new_mem != NULL);
    assert(segment_0 != NULL);

    new_mem->segments = Seq_new(1);
    Seq_addhi(new_mem->segments, segment_0);
    new_mem->unmapped = Seg_new(1);
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
    int length = Seq_length(new_mem->segments);
    for(int i = 0; i < length; i++) {
        Seg_T to_free = Seq_get(new_mem->segments, i);
        Seg_free(to_free);
    }

    Seq_free(new_mem->segments);
    Seg_free(new_mem->unmapped);
    free(new_mem);
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
    Seg_T new_seg = Seg_new(rc);
    	for (int i = 0; i < (int)rc; i++) {
            Seg_addhi(new_seg, 0);
        }
    uint32_t id;
    if(Seg_length(new_mem->unmapped) != 0) {
        id = Seg_remhi(new_mem->unmapped);
        Seg_T old_sequence = Seq_put(new_mem->segments, id, new_seg);
        Seg_free(old_sequence);
    } else {
        Seq_addhi(new_mem->segments, new_seg);
        id = Seq_length(new_mem->segments) - 1;
    }
    return id;
}

/**************************************************************
 *                     sequence.c
 **************************************************************/

void Seq_free(Seq_T seq) 
{
    assert(seq != NULL);
    free(seq->array);
    free(seq);
}

Seq_T Seq_new(int hint) 
{
    assert(hint > 0);
    Seq_T new_seq = malloc(sizeof(struct Seq_T));
    new_seq->array = malloc(sizeof(struct Seg_T) * hint);
    new_seq->length = 0;
    new_seq->size = hint;
    return new_seq;
}

Seg_T Seq_get(Seq_T seq, int i) 
{
    assert(seq != NULL);
    assert(i >= 0 && i < seq->length);
    return seq->array[i];
}

Seg_T Seq_put(Seq_T seq, int i, Seg_T seg) 
{
    assert(seq != NULL);
    assert(i >= 0 && i < seq->length);
    Seg_T prev = seq->array[i];
    seq->array[i] = seg;
    return prev;
}

int Seq_length(Seq_T seq) 
{
    assert(seq != NULL);
    return seq->length;
}

void Seq_addhi(Seq_T seq, Seg_T seg)
{
    assert(seq != NULL);
    assert(seq->array != NULL);
    if (seq->length == seq->size) {
        Seg_T *new_array = realloc(seq->array, sizeof(struct Seg_T) * seq->size 
        * 2);
        seq->array = new_array;
        seq->size *= 2;
    }
    seq->array[seq->length] = seg;
    seq->length += 1;    
}

/**************************************************************
 *                     segment.c
 **************************************************************/

void Seg_free(Seg_T seg) {
    assert(seg != NULL);
    free(seg->array);
    free(seg);
}

Seg_T Seg_new(int hint) {
    assert(hint > 0);
    Seg_T new_seg = malloc(sizeof(struct Seg_T));
    new_seg->array = malloc(sizeof(uint32_t) * hint);
    new_seg->length = 0;
    new_seg->size = hint;
    return new_seg;
}

uint32_t Seg_get(Seg_T seg, int i) {
    assert(seg != NULL);
    assert(i >= 0 && i < seg->length);
    return seg->array[i];
}

uint32_t Seg_put(Seg_T seg, int i, uint32_t val) {
    assert(seg != NULL);
    assert(i >= 0 && i < seg->length);
    uint32_t prev = seg->array[i];
    seg->array[i] = val;
    return prev;
}

int Seg_length(Seg_T seg) {
    assert(seg != NULL);
    return seg->length;
}

void Seg_addhi(Seg_T seg, uint32_t val) {
    assert(seg != NULL);
    assert(seg->array != NULL);
    if (seg->length == seg->size) {
        uint32_t *new_array = realloc(seg->array, sizeof(uint32_t) * seg->size 
        * 2);
        seg->array = new_array;
        seg->size *= 2;
    }
    seg->array[seg->length] = val;
    seg->length += 1;    
}

uint32_t Seg_remhi(Seg_T seg) {
    assert(seg); 
    assert(seg->length > 0);
    seg->length--;
    return seg->array[seg->length];
}

/**************************************************************
 *                     execute.c
 **************************************************************/

uint32_t reg[8] = {0};
uint32_t prog_counter = 0;

/* 
 * Name: input())
 * Description: Takes in a file pointer pointing to stdin and 
 *              the value c. Gets a char from stdin and if 
 *              that char is equal to EOF, have reg[c] = -1;
 *              If char is not equal to EOF, then reg[c] is equal
 *              the value inputted. 
 * Expectations: input pointer is equal to stdin.
*/
void input(FILE* input, uint32_t c) 
{
    uint32_t value = getc(input);
    if ((int)value == EOF) {
        reg[c] = (uint32_t) (-1);
    }
    reg[c] = value;
}

/* 
 * Name: loadProgram())
 * Description: Takes in memory struct, value b, and c. Segment at 
 * m[r[b]] is duplicated and loaded onto m[0] which is then replaced.
 * Program counter is set to point to reg[c] - 1. 
 * Expectations: none
*/
void loadProgram(mem new_mem, uint32_t b, uint32_t c) 
{
   if (reg[b] != 0) {
    Seg_T segment_b = Seq_get(new_mem->segments, reg[b]);
       /* duplicate segment b */
    uint32_t length = Seg_length(segment_b);
    Seg_T dup = Seg_new(length);
       for(int i = 0; i < (int)length; i++) {
            uint32_t instr_word = Seg_get(segment_b, i);
            Seg_addhi(dup, instr_word);
        }
        /* put segment b in the position of segment 0 */
        Seq_put(new_mem->segments, 0, dup);
    }
   /* Update the counter to be 1 less than desired value, because the 
    * instruction ends by incrementing counter by 1
    */
   prog_counter = reg[c] - 1;
}

/* 
 * Name: executeInstr()
 * Description: Takes in the instruction sequence. Instantiates a memory
 *              struct, passing the sequence of instructions. Loops 
 *              continuously to execute instructions. Checks special case
 *              where the instruction is load value, where the instruction
 *              components are different. Otherwise, unpack the three
 *              register values from the instruction and call the
 *              execute helper. Finally, increment the program counter.
 * Expectations: None
*/
void executeInstr(Seg_T segment_0) 
{
    mem memory = memNew(segment_0);

    /* Halt instruction will end program, we can run continously */
    while(1) {
        uint32_t instr_word, opcode, a, b, c, val;
        instr_word = (memory->segments->array[0])->array[prog_counter];
        uint32_t temp = instr_word;
        opcode = temp >> 28;
        /* Case where instr is load value, simply handle here */
        if(opcode == 13) {
            a = instr_word;
            a = a << 4;
            a = a >> 29;

            val = instr_word;
            val = val << 7;
            val = val >> 7;
            reg[a] = val;
        } else {
            a = instr_word;
            a = a << 23;
            a = a >> 29;

            b = instr_word;
            b = b << 26;
            b = b >> 29;

            c = instr_word;
            c = c << 29;
            c = c >> 29;
            switch(opcode) {
                case 0 : 
                     if (reg[c] != 0) {
                         reg[a] = reg[b];
                     }
                    break;
                case 1 :
                    reg[a] = (memory->segments->array[reg[b]])->array[reg[c]];
                    break;
                case 2 : 
                    (memory->segments->array[reg[a]])->array[reg[b]] = reg[c];
                    break;
                case 3 : 
                    reg[a] = (reg[c] + reg[b]) % 4294967296;
                    break;
                case 4 :
                    reg[a] = (reg[b] * reg[c]) % 4294967296;
                    break;
                case 5 :
                    reg[a] = reg[b] / reg[c];
                    break;
                case 6 : 
                    reg[a] = ~(reg[b] & reg[c]);
                    break;
                case 7 : 
                    memFree(memory);
                    exit(0);
                    break;
                case 8 : 
                    reg[b] = mapSegment(memory, reg[c]);
                    break;
                case 9 :   
                    Seg_addhi(memory->unmapped, reg[c]);
                    break;
                case 10 : 
                    putchar(reg[c]);
                    break;
                case 11 : 
                    input(stdin, c);
                    break;
                case 12 : 
                    loadProgram(memory, b, c);
                    break;
            }
        }
        prog_counter++;
    }  
}