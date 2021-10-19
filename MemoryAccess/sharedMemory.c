#include "sharedMemory.h"
#define MEMORY_ERROR (-1)

static int * getMemBlock(char *filename, int size)
{

    key_t key;

    key = ftok(filename, 1);
    if (key == MEMORY_ERROR)
    {
        return MEMORY_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);
}

char *attach_memblock(char *filename, int size)
{
    int id_block = getMemBlock(filename, size);

    if (id_block == MEMORY_ERROR)
    {
        return 0;
    } 
}