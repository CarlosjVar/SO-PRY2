#include "../sharedMem.h"
#include "../models/memoryBlock.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#define IPC_RESULT_ERROR (-1)

void spyMemory(){

    int *memorySize = get_array_size(FILENAME, sizeof(int));
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

        
        
        if ((i+1) % 3 == 0)
        {
            printf("\n");
        } 
    }
    printf("\n");
}

void spyProcesses(){

    int *memorySize = get_array_size(FILENAME, sizeof(int));
    //struct memoryBlock *processes[memorySize[0]];
    struct memoryBlock *baseBlock;
    struct memoryBlock *queue;
    int requiredBlockSize = memorySize[0]* sizeof(baseBlock);
    baseBlock = attach_memory_block(FILENAME, requiredBlockSize);
    queue = get_ready_queue(FILENAME);


    for (int i = 0; i < memorySize[0]; i++)
    {
        
        if (baseBlock[i].status != 0)
        {
            printf("* Process ID: %d , Estado: Ejecutando", baseBlock[i].PID);
            printf("\n");
        }
        
    }

    for (int i = 0; i < QUEUE_SIZE; i++){
        
        if (queue[i].PID != -1 )
        {
            printf("+ Process ID: %d , Estado: ", baseBlock[i].PID);
            if (queue[i].status == 3)
            {
                printf("Accediendo a Memoria");

            }else{
                printf("Bloqueado");

            }
            printf("\n");        
        }        
    }
}

int main(int argc, char const *argv[])
{
    printf("Digite 1 para espiar la Memoria. Digite 2 para espiar los procesos. \n");
    int eleccion;
    scanf("%d", &eleccion);

    printf("\nEspiado Iniciado... \n\n");
    if(eleccion == 1){
        spyMemory();

    }else if(eleccion == 2){
        spyProcesses();

    }else{
        printf("El valor digitado es invalido\n");
    }

    printf("\n");
    return 0;
}