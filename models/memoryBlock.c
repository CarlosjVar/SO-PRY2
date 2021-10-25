#include "memoryBlock.h"

void insert_process(int init, int p_size, struct memoryBlock *blockList, int arraySize)
{
    while (p_size > 0)
    {

        blockList[init++].status = 1;
        p_size--;
    }
    for (int i = 0; i < arraySize; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, blockList[i].status);
    }
}

void first_fit(struct memoryBlock *blockList, int p_size, int arraySize)
{

    int size = 0;
    for (int i = 0; i < arraySize; i++)
    {

        if (blockList[i].status == 0)
        {
            size += 1;
            if (size >= p_size)
            {
                insert_process(i - p_size + 1, p_size, blockList, arraySize);
                break;
            }
            continue;
        }
        size = 0;
    }
}

void best_fit(struct memoryBlock *blockList, int p_size, int arraySize)
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
        insert_process(actual_space[0], p_size, blockList, arraySize);
}

void worst_fit(struct memoryBlock *blockList, int p_size, int arraySize)
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
        insert_process(actual_space[0], p_size, blockList, arraySize);
}