/**************************************************************
 *
 *                     um.c
 *
 *     Assignment: um
 *     Authors:    Devan Venkataraman, Cheryl Melwani, 
 *     Date:       4/19/2021
 *
 *     Purpose: Driver for the um program. Reads in file
 *              from command line and links both to um_loader
 *              module and execute module by beginning the
 *              read of instructions.
 *              
 *              
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "um_loader.h"
#include "execute.h"

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

    Seq_T segment_0 = load_um(fp);
    fclose(fp);

    executeInstr(segment_0);
    exit(0);
}