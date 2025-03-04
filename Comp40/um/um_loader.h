/**************************************************************
 *
 *                     um_loader.h
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Header file for um_loader module.
 *              
 *     
 * 
 **************************************************************/

#ifndef UM_LOADER_H_
#define UM_LOADER_H_

#include <stdlib.h>
#include <stdio.h>
#include "seq.h"
#include "bitpack.h"

Seq_T load_um(FILE* fp);
uint32_t getInstruction(FILE *fp, int byte1);

#endif
