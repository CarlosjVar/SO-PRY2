#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "blockwriting.c"
// #include "blockreading.c"
// #include "blockdestruction.c"

struct memoryBlock
{

    int PID;
    int status; //0 = libre, 1 = bloqueado, 2 = corriendo
};

void insert_process(int init, int p_size, struct memoryBlock *blockList, int arraySize);
void first_fit(struct memoryBlock *blockList, int p_size, int arraySize);
void best_fit(struct memoryBlock *blockList, int p_size, int arraySize);
void worst_fit(struct memoryBlock *blockList, int p_size, int arraySize);
#endif