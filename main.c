
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MEMORY_ERROR (-1)


int getMemBlock(char *filename, int size)
{
    key_t key;

    key = ftok(filename, 1);
    if (key == MEMORY_ERROR)
    {
        return MEMORY_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);
}



char attach_memblock(char *filename, int size)
{
    int id_block = getMemBlock(filename, size);

    if (id_block == MEMORY_ERROR)
    {
        return 0;
    } 
    printf("asdasdas");
    char *result = shmat(id_block,NULL,0);

    if(result == (char *) MEMORY_ERROR){
        printf("error \n ");
        return NULL;
    }
    return result;
}


int main(int argc, char const *argv[])
{   
    char *var = "pepito.txt";
    char *block = attach_memblock(var,4096);
    printf("%s",block);
    return 0;
}
