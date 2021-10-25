#include "threadStruct.h"
struct threadStruct *threadStruct()
{
    struct threadStruct *currentProcess = malloc(sizeof(struct threadStruct));
    currentProcess->size = malloc(sizeof(int));
    currentProcess->runtime = malloc(sizeof(int));
    currentProcess->id = malloc(sizeof(int));
    currentProcess->allocationAlgorithm = malloc(sizeof(int));

    return currentProcess;
}
void insert_process(int init, int p_size, struct memoryBlock *blockList, int arraySize, int pid)
{
    struct memoryBlock *newBlock = malloc(sizeof(struct memoryBlock));
    newBlock->PID = pid;
    newBlock->status = 1;
    while (p_size > 0)
    {
        // printf("En el espacio %d", init);

        blockList[init] = *newBlock;
        init++;
        p_size--;
    }
    // for (int i = 0; i < arraySize; i++)
    // {
    //     printf("El  bloque  [%d] tiene PID %d  status %d  \n", i, blockList[i].PID, blockList[i].status);
    // }
}

int first_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid)
{

    int size = 0;
    for (int i = 0; i < arraySize; i++)
    {

        if (blockList[i].status == 0)
        {
            size += 1;
            if (size >= p_size)
            {
                insert_process(i - p_size + 1, p_size, blockList, arraySize, pid);
                return i - p_size + 1;
            }
            continue;
        }
        size = 0;
    }
    return -1;
}

int best_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid)
{
    int size = 0;
    int index = 0;
    int actual_space[] = {0, 0};
    for (int i = 0; i < arraySize; i++) //bastante segura que hay que cambiar el tamaño
    {
        if (blockList[i].status == 0)
        {
            if (size == 0)
                index = i;
            size += 1;
        }
        if (size > 0 && (blockList[i].status != 0 || i == arraySize - 1))
        { //aqui tambien
            if (size >= p_size && (size < actual_space[1] || actual_space[1] == 0))
            {
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if (actual_space[1] >= p_size)
    {

        insert_process(actual_space[0], p_size, blockList, arraySize, pid);
        return actual_space[0];
    }
    else
    {
        return -1;
    }
}

int worst_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid)
{

    int size = 0;
    int index = 0;
    int actual_space[] = {0, 0};
    for (int i = 0; i < arraySize; i++) //bastante segura que hay que cambiar el tamaño
    {
        if (blockList[i].status == 0)
        {
            if (size == 0)
                index = i;
            size += 1;
        }
        if (size > 0 && (blockList[i].status != 0 || i == arraySize - 1))
        { //aqui tambien
            if (size >= p_size && (size > actual_space[1] || actual_space[1] == 0))
            {
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if (actual_space[1] >= p_size)
    {
        insert_process(actual_space[0], p_size, blockList, arraySize, pid);
        return actual_space[0];
    }
    else
    {
        return -1;
    }
}
