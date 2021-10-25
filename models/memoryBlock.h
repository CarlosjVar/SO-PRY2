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
    int status; //0 = libre, 1 = bloqueado, 2 = corriendo, 3 = Usando memoria
};

#endif