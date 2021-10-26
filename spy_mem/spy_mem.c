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

void spyMemory(){

    int *memorySize = get_array_size(FILENAME, sizeof(int));
    //struct memoryBlock *processes[memorySize[0]];
    struct memoryBlock *baseBlock;
    int requiredBlockSize = memorySize[0]* sizeof(baseBlock);
    baseBlock = attach_memory_block(FILENAME, requiredBlockSize);

    for (int i = 0; i < memorySize[0]; i++)
    {
        printf("[ Espacio:%d ID:%d ", i, baseBlock[i].PID);

        if (baseBlock[i].status == 0)
        {
            printf("Vacio ]");

        }else{

            printf("En uso ]");

        }

        
        
        if ((i+1) % 5 == 0)
        {
            printf("\n");
        } 
    }
}

int main(int argc, char const *argv[])
{
    printf("Espiado Iniciado... \n\n");
    spyMemory();
    printf("\n");
    return 0;
}
