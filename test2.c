#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "./models/memoryBlock.h"
#define FILENAME "memblock.c"


void insert_process(int init,int p_size)
{
    int array[] = {1,0,1,1,0,0,0,1,1,0};
    while (p_size>0)
    {
        array[init++]=1;
        p_size--;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, array[i]);
    }

}


void first_fit(int p_size)
{
    int array[] = {1,0,0,1,0,0,0,1,1,0};
    int size = 0;
    for (int i = 0; i < 10; i++)
    {

        if(array[i] == 0){
            size += 1;
            if(size >= p_size)
            {
                insert_process( i-p_size+1, p_size);
                break;
            }
            continue;
        }
        size = 0;
    }


}

void best_fit(int p_size)
{
    int array[] = {1,0,1,1,0,0,0,1,1,0};
    int size = 0;
    int index = 0;
    int actual_space[] ={0,0};
    for (int i = 0; i < 10; i++)
    {
        if(array[i] == 0){
            if(size == 0)
                index=i;
            size += 1;
        }
        if(size > 0 && (array[i] == 1 || i == 9 )){
            if(size>= p_size && (size<actual_space[1] || actual_space[1]==0)){
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if(actual_space[1]>=p_size)
        insert_process(actual_space[0], actual_space[1]);
}

void worst_fit(int p_size)
{
    int array[] = {1,0,1,1,0,0,0,1,1,0};
    int size = 0;
    int index = 0;
    int actual_space[] ={0,0};
    for (int i = 0; i < 10; i++)
    {
        if(array[i] == 0){
            if(size == 0)
                index=i;
            size += 1;
        }
        if(size > 0 && (array[i] == 1 || i == 9 )){
            if(size>= p_size && (size>actual_space[1] || actual_space[1]==0)){
                actual_space[0] = index;
                actual_space[1] = size;
            }
            size = 0;
        }
    }
    if(actual_space[1]>=p_size)
        insert_process(actual_space[0], actual_space[1]);
}



int main(int argc, char const *argv[])
{

    struct memoryBlock * blockList;
    int requiredBlockSize = 10 * sizeof(*blockList);
    int shmid;
    
    shmid = get_shared_memory(FILENAME, requiredBlockSize);

    blockList = (struct memoryBlock *)shmat(shmid, 0, 0);
    if (blockList == (void *)-1)
    {
        perror("schmat error");
        exit(1);
    }

    worst_fit(1);
     
    

}
