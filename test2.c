#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "./models/memoryBlock.h"
#include "sharedMem.h"
#define FILENAME "memblock.c"
int main(int argc, char const *argv[])
{

    struct memoryBlock *baseBlock;
    int *arraySize;
    arraySize = get_array_size(FILENAME, sizeof(int));
    int requiredBlockSize = arraySize[0]* sizeof(baseBlock);

    baseBlock = attach_memory_block(FILENAME, requiredBlockSize);


    for (int i = 0; i < arraySize[0]; i++)
    {
        printf("El  bloque tiene PID %d  estatus %d  \n", baseBlock[i].PID, baseBlock[i].status);
    }
    return 0;
}
