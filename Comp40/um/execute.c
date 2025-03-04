/**************************************************************
 *
 *                     execute.c
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Holds the implementation of the execute model. 
 *     Handles the implementation of several instructions such
 *     as conditionalMove, add, multiply, divide, bitwiseNAND,
 *     halt, output, input, loadProgram, loadValue.
 *     Fetch, decode, execute cycle happens. 
 *
 **************************************************************/

#include "execute.h"

uint32_t reg[8] = {0};
uint32_t prog_counter = 0;

/* 
 * Name: conditionalMove()
 * Description: Takes in a, b, c values and passes them to the 
 *              registers. Carries out the condiitonalMove 
 *              instruction. 
 * Expectations: none
*/
void conditionalMove(uint32_t a, uint32_t b, uint32_t c) 
{
    if (reg[c] != 0) {
        reg[a] = reg[b];
    }
}

/* 
 * Name: addition()
 * Description: Takes in a, b, c values and passes them to the 
 *              registers. Carries out the addition 
 *              instruction. 
 * Expectations: none
*/
void addition(uint32_t a, uint32_t b, uint32_t c) 
{
    /* 2^32 = 4294967296 */
    reg[a] = (reg[c] + reg[b]) % 4294967296;
}

/* 
 * Name: multplication()
 * Description: Takes in a, b, c values and passes them to the 
 *              registers. Carries out the multiplication
 *              instruction. 
 * Expectations: none
*/
void multiplication(uint32_t a, uint32_t b, uint32_t c) 
{
    reg[a] = (reg[b] * reg[c]) % 4294967296;
}

/* 
 * Name: division()
 * Description: Takes in a, b, c values and passes them to the 
 *              registers. Carries out the division
 *              instruction. 
 * Expectations: none
*/
void division(uint32_t a, uint32_t b, uint32_t c) 
{
    reg[a] = reg[b] / reg[c];
}

/* 
 * Name: bitwiseNAND()
 * Description: Takes in a, b, c values and passes them to the 
 *              registers. Carries out the bitwiseNAND  
 *              instruction. 
 * Expectations: none
*/
void bitwiseNAND(uint32_t a, uint32_t b, uint32_t c) 
{
    reg[a] = ~(reg[b] & reg[c]);
}

/* 
 * Name: bitwiseNAND()
 * Description: Takes in memory struct and frees the memory before
 *              exiting the program using exit(0)
 * Expectations: memory struct is non null
*/
void halt(mem memory) 
{
    memFree(memory);
    exit(0);
}

/* 
 * Name: output()
 * Description: Takes the value c. Outputs a char between 0 and 255 using
 *              putchar()
 * Expectations: none
*/
void output(uint32_t c) 
{
    putchar(reg[c]);
}

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
void loadProgram(mem memory, uint32_t b, uint32_t c) 
{
   if (reg[b] != 0) {
       Seq_T segment_b = Seq_get(memory->segments, reg[b]);
       /* duplicate segment b */
       uint32_t length = Seq_length(segment_b);
       Seq_T dup = Seq_new(length);
       for(int i = 0; i < (int)length; i++) {
           uint32_t instr_word = (uint32_t) (uintptr_t) Seq_get(segment_b, i);
           Seq_addhi(dup, (void*) (uintptr_t) instr_word);
        }
        /* put segment b in the position of segment 0 */
        Seq_put(memory->segments, 0, dup);
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
void executeInstr(Seq_T segment_0) 
{

    mem memory = memNew(segment_0);
    
    /* Halt instruction will end program, we can run continously */
    while(1) {
        uint32_t instr_word, opcode, a, b, c, val;
        /* Use our own segmentedLoad to access the current instruction
        *  at segment 0, offset @ program counter
        */
        instr_word = segmentedLoad(memory, 0, prog_counter);
        opcode = Bitpack_getu(instr_word, 4, 28);
        
        /* Case where instr is load value, simply handle here */
        if(opcode == 13) {
            a = Bitpack_getu(instr_word, 3, 25);
            val = Bitpack_getu(instr_word, 25, 0);
            reg[a] = val;
        } else {
            a = Bitpack_getu(instr_word, 3, 6);
            b = Bitpack_getu(instr_word, 3, 3);
            c = Bitpack_getu(instr_word, 3, 0);

            executeHelper(memory, opcode, a, b, c);
        }
        prog_counter++;
    }  
}

/* 
 * Name: executeHelper()
 * Description: Takes in the memory struct and the four components for an
 *              instruction: the opcode, and register a, b, and c values.
 *              Performs a switch on the opcode to locate the correct
 *              instruction and calls the corresponding instruction
 *              helper function.
 * Expectations: None
*/
void executeHelper(mem memory, uint32_t opcode, uint32_t a, uint32_t b, 
uint32_t c) 
{
    switch(opcode) {
        case 0 : 
            conditionalMove(a, b, c);
            break;
        case 1 :
            reg[a] = segmentedLoad(memory, reg[b], reg[c]);
            break;
        case 2 : 
            segmentedStore(memory, reg[a], reg[b], reg[c]);
            break;
        case 3 : 
            addition(a, b, c);
            break;
        case 4 :
            multiplication(a, b, c);
            break;
        case 5 :
            division(a, b, c);
            break;
        case 6 : 
            bitwiseNAND(a, b, c);
            break;
        case 7 : 
            halt(memory);
            break;
        case 8 : 
            reg[b] = mapSegment(memory, reg[c]);
            break;
        case 9 : 
            unmapSegment(memory, reg[c]);
            break;
        case 10 : 
            output(c);
            break;
        case 11 : 
            input(stdin, c);
            break;
        case 12 : 
            loadProgram(memory, b, c);
            break;
    }
}