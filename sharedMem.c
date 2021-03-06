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

struct memoryBlock *get_ready_queue(char *filename)
{
    int memSegment = get_queue_id(filename);

    if (memSegment == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }
    struct memoryBlock *memoryBlock;
    memoryBlock = (struct memoryBlock *)shmat(memSegment, 0, 0);

    if (memoryBlock == (struct memoryBlock *)IPC_RESULT_ERROR)
    {
        perror("schmat error");
        exit(1);
    }
    return memoryBlock;
}

int get_queue_id(char *filename)
{
    key_t key;

    key = ftok(filename, 2);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, QUEUE_SIZE, 0644 | IPC_CREAT);
}

int create_spy_id(char *filename, int size){
    key_t key;

    key = ftok(filename, 3);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, QUEUE_SIZE, 0644 | IPC_CREAT);
}

int create_processGenerator_id(char *filename, int size){
    key_t key;

    key = ftok(filename, 4);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, QUEUE_SIZE, 0644 | IPC_CREAT);
}

int *get_spy_id(char *filename, int size){

    int memblock = create_spy_id(filename, size);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }

    int *processId;
    processId = (int *)shmat(memblock, 0, 0);

    if (processId == (int *)IPC_RESULT_ERROR)
    {
        perror("schmat error");
        exit(1);
    }
    return processId;
}

int *get_processGenerator_id(char *filename, int size){
    int memblock = create_processGenerator_id(filename, size);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }

    int *processId;
    processId = (int *)shmat(memblock, 0, 0);

    if (processId == (int *)IPC_RESULT_ERROR)
    {
        perror("schmat error");
        exit(1);
    }
    return processId;
}

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

int create_array_size(char *filename, int size)
{
    key_t key;

    key = ftok(filename, 1);
    if (key == IPC_RESULT_ERROR)
    {
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0666 | IPC_CREAT);
}

int *get_array_size(char *filename, int size)
{
    int memblock = create_array_size(filename, size);

    if (memblock == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }

    int *arraySize;
    arraySize = (int *)shmat(memblock, 0, 0);

    if (arraySize == (int *)IPC_RESULT_ERROR)
    {
        perror("schmat error");
        exit(1);
    }
    return arraySize;
}

struct memoryBlock *create_memory_block(char *filename, int size)
{

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

bool detach_memory_block(char *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *filename)
{

    int memblock = get_shared_memory(filename, 0);
    int sizeMemblock = create_array_size(filename, 0);
    int readyQueue = get_queue_id(filename);
    int generatorBlock = create_processGenerator_id(filename,0);
    int spyBlock = create_spy_id(filename,0);
    if (memblock == IPC_RESULT_ERROR || sizeMemblock == IPC_RESULT_ERROR || readyQueue == IPC_RESULT_ERROR || spyBlock == IPC_RESULT_ERROR || generatorBlock == IPC_RESULT_ERROR)
    {
        printf("Imposible destruir memoria, archivo no encontrado\n");
        return NULL;
    }
    (shmctl(generatorBlock, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    (shmctl(spyBlock, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    (shmctl(sizeMemblock, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    (shmctl(readyQueue, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    return (shmctl(memblock, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}
