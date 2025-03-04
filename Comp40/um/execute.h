/**************************************************************
 *
 *                     execute.h
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Holds the interface for the execute module 
 *
 **************************************************************/

#ifndef EXECUTE_H_
#define EXECUTE_H_

#include "memory.h"
#include "bitpack.h"

void executeInstr(Seq_T instructions);
void readinstr(uint32_t instruction);
void executeHelper(mem memory, uint32_t opcode, uint32_t a, uint32_t b, 
uint32_t c);

#endif