#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "./models/memoryBlock.h"
#include "sharedMem.h"
#define FILENAME "memblock.c"


void insert_process( int init,int p_size, struct memoryBlock * blockList)
{
    while (p_size>0)
    {
        blockList[init++].status =1;
        p_size--;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, blockList[i].status);
    }

}


void first_fit(struct memoryBlock * blockList, int p_size)
{

    int size = 0;
    for (int i = 0; i < 10; i++)
    {

        if(blockList[i].status  == 0){
            size += 1;
            if(size >= p_size)
            {
                insert_process( i-p_size+1, p_size, blockList);
                break;
            }
            continue;
        }
        size = 0;
    }


}

void best_fit(struct memoryBlock * blockList, int p_size)
{
    int size = 0;
    int index = 0;
    int actual_space[] ={0,0};
    for (int i = 0; i < 10; i++) //bastante segura que hay que cambiar el tamaño
    {
        if(blockList[i].status == 0){
            if(size == 0)
                index=i;
            size += 1;
        }
        if(size > 0 && (blockList[i].status != 0 || i == 9 )){ //aqui tambien
            if(size>= p_size && (size<actual_space[1] || actual_space[1]==0)){
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if(actual_space[1]>=p_size)
        insert_process(actual_space[0], p_size, blockList);
}

void worst_fit(struct memoryBlock * blockList, int p_size)
{
    
    int size = 0;
    int index = 0;
    int actual_space[] = {0,0};
    for (int i = 0; i < 10; i++) //bastante segura que hay que cambiar el tamaño
    {
        if(blockList[i].status == 0){
            if(size == 0)
                index=i;
            size += 1;
        }
        if(size > 0 && (blockList[i].status != 0 || i == 9 )){ //aqui tambien
            if(size>= p_size && (size>actual_space[1] || actual_space[1]==0)){
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if(actual_space[1]>=p_size)
        insert_process(actual_space[0], p_size, blockList);
}



int main(int argc, char const *argv[])
{

    struct memoryBlock *baseBlock;
    int *arraySize;
    arraySize = get_array_size(FILENAME, sizeof(int));
    int requiredBlockSize = arraySize[0]* sizeof(baseBlock);

    baseBlock = attach_memory_block(FILENAME, requiredBlockSize);

    baseBlock = (struct memoryBlock *)shmat(shmid, 0, 0);
    if (baseBlock == (void *)-1)
    {
        perror("schmat error");
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, blockList[i].status);
    }
    printf("---------------------------------------\n");
    first_fit(blockList, 1);

}
