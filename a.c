#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "./models/memoryBlock.h"
#define FILENAME "memblock.c"
int main(int argc, char const *argv[])
{

    struct memoryBlock *baseBlock;
    int requiredBlockSize = 10 * sizeof(*baseBlock);
    int shmid;

    shmid = create_memory_block(FILENAME, requiredBlockSize);

    baseBlock = (struct memoryBlock *)shmat(shmid, 0, 0);
    if (baseBlock == -1)
    {
        perror("schmat error");
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("El  bloque tiene PID %d  status %d", baseBlock[i].PID, baseBlock[i].status);
    }
    return 0;
}
