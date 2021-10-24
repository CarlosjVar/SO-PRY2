#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sharedMem.h"

#define BLOCK_SIZE 4096
#define FILENAME "memblock.c"
#define IPC_RESULT_ERROR (-1)

int get_shared_memory(char *filename, int size)
{
    key_t key;

    key = ftok(filename, 0);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644);
}

int create_shared_memory(char *filename, int size)
{

    key_t key;

    key = ftok(filename, 0);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0666 | IPC_CREAT);
}

struct memoryBlock *create_memory_block(char *filename, int size)
{

    printf("Llega aquí");
    int memblock = create_shared_memory(filename, size);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }
    struct memoryBlock *baseBlock;
    baseBlock = (struct memoryBlock *)shmat(memblock, 0, 0);

    if (baseBlock == (struct memoryBlock *)IPC_RESULT_ERROR)
    {
        printf("No se pudo reservar el espacio\n");
        return NULL;
    }

    return baseBlock;
}
struct memoryBlock *attach_memory_block(char *filename, int size)
{
    int memblock = get_shared_memory(filename, size);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }
    struct memoryBlock *baseBlock;
    baseBlock = (struct memoryBlock *)shmat(memblock, 0, 0);

    if (baseBlock == (struct memoryBlock *)IPC_RESULT_ERROR)
    {
        perror("schmat error");
        exit(1);
    }

    return baseBlock;
}

bool detach_memory_block(struct memoryBlock *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *filename)
{

    int memblock = get_shared_memory(filename, 0);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("Imposible destruir memoria, archivo no encontrado\n");
        return NULL;
    }
    return (shmctl(memblock, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}

int *setArraySize(char *filename, int *size)
{
    key_t key;

    key = ftok(filename, 1);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }
    int memblock = shmget(key, sizeof(int), 0666 | IPC_CREAT);
    int sharedSize;
    sharedSize = (int *)shmat(memblock, 0, 0);
    sharedSize = size;
    shmdt(sharedSize);
    return size;
}

int *getArraySize(char *filename)
{
    key_t key;

    key = ftok(filename, 1);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }
    int *memblock = shmget(key, sizeof(int), 0666);
    int *sharedSize;
    sharedSize = (int *)shmat(memblock, 0, 0);

    shmdt(sharedSize);
    return sharedSize;
}