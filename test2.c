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
    int arraySize = getArraySize(FILENAME);
    int requiredBlockSize = arraySize * sizeof(*baseBlock);
    baseBlock = attach_memory_block(FILENAME, requiredBlockSize);
    // int shmid;

    // shmid = get_shared_memory(FILENAME, requiredBlockSize);

    // baseBlock = (struct memoryBlock *)shmat(shmid, 0, 0);
    // if (baseBlock == (void *)-1)
    // {
    //     perror("schmat error");
    //     exit(1);
    // }

    for (int i = 0; i < arraySize; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", baseBlock[i].PID, baseBlock[i].status);
    }
    detach_memory_block(baseBlock);
    return 0;
}