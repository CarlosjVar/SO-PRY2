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
    int arraySize;
    scanf("%d", &arraySize);
    int requiredBlockSize = arraySize * sizeof(*baseBlock);

    int shmid;
    // Our program
    baseBlock = create_memory_block(FILENAME, requiredBlockSize);

    //printf("\nWritting to memory succesful--\n");
    if (baseBlock == (void *)-1)
    {
        perror("schmat error");
        exit(1);
    }
    setArraySize(FILENAME, arraySize);
    detach_memory_block(baseBlock);
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
