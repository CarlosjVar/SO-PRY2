#include "../sharedMem.h"
#include "../models/memoryBlock.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define IPC_RESULT_ERROR (-1)
void startMemory()
{
    struct memoryBlock *baseBlock;
    printf("Ingrese la cantidad de espacios de memoria que desea reservar \n");
    int n;
    scanf("%d", &n);
    int requiredBlockSize = n * sizeof(*baseBlock);

    int shmid;

    // Our program
    baseBlock = create_memory_block(FILENAME, requiredBlockSize);

    //printf("\nWritting to memory succesful--\n");
    if (baseBlock == (void *)-1)
    {
        perror("schmat error");
        exit(1);
    }
    baseBlock[0].PID = 2;
    baseBlock[0].status = 1;
    baseBlock[1].PID = 1;
    baseBlock[1].status = 2;
    baseBlock[2].PID = 24;
    baseBlock[2].status = 1;
    shmdt((void *)baseBlock);
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
