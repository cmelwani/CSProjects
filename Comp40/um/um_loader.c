/**************************************************************
 *
 *                     um_loader.c
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: reads and processes the provided file, parsing
 *              into 32-bit instructions.
 *              
 *     
 * 
 **************************************************************/

#include "um_loader.h"

/* 
 * Name: load_um()
 * Description: Calculates the number of instructions that the
 *              file holds and instantiates a sequence to
 *              store the instructions in memory.
 * Expectations: The number of bytes in the file is divisible
 *               by 4, aka only complete 32-bit instructions.
*/
Seq_T load_um(FILE* fp) {

    /* Calculate the number of bytes of the instructions */
    fseek(fp, 0L, SEEK_END);
    long int length = ftell(fp);

    if (length == 0 || length % 4 != 0) {
        // TODO: what type of error here???
        exit(EXIT_FAILURE);
    }

    rewind(fp);

    /* Create a sequence to hold the 32 bit instruction codes */
    Seq_T segment_0 = Seq_new(length/4);
    // int seqlength = Seq_length(segment_0);
    // printf("# of instructions in file is: %ld\n", length/4);

    int byte1;
    while ((byte1 = getc(fp)) != EOF) {
        Seq_addhi(segment_0, (void*)(uintptr_t) getInstruction(fp, byte1));
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
    int byte2 = getc(fp);
    int byte3 = getc(fp);
    int byte4 = getc(fp);

    instr_code = Bitpack_newu(instr_code, 8, 24, byte1);
    instr_code = Bitpack_newu(instr_code, 8, 16, byte2);
    instr_code = Bitpack_newu(instr_code, 8, 8, byte3);
    instr_code = Bitpack_newu(instr_code, 8, 0, byte4);
    return (uint32_t) instr_code;
}