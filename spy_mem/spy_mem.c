#include "../sharedMem.h"
#include "../models/memoryBlock.h"
#include <pthread.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
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
    shmdt((void *)baseBlock);
}

void spyProcesses(){

    struct memoryBlock *queue;
    queue = get_ready_queue(FILENAME);
    int currentId = -5;


    for (int i = 0; i < QUEUE_SIZE; i++){
        
        if (queue[i].PID != -1 )
        {
            printf("* Process ID: %d , Estado: ", queue[i].PID);
            switch (queue[i].status)
            {
            case 1:
                printf("Bloqueado");
                break;

            case 2:
                printf("Ejecutando");
                break;
            default:
                printf("Accediendo a Memoria");
                break;
            }  
            printf("\n");                
        }        
    }
    shmdt((void *)queue);
}

int main(int argc, char const *argv[])
{
    sem_t *sem;
    sem = sem_open(SEMAPHORE_NAME_QUEUE, 0, 0644, 0);

    int *pidBlock = get_spy_id(FILENAME, sizeof(int));
    pidBlock[0] = getpid(); 

    shmdt((void *)pidBlock);

    while (true)
    {
        printf("\nDigite 1 para espiar la Memoria, 2 para espiar los procesos o 3 para salir. \n");
        int eleccion;
        scanf("%d", &eleccion);        

        switch (eleccion)
        {
        case 1:
            printf("\nEspiado Iniciado... \n\n");
            sem_wait(sem);
            spyMemory();
            sem_post(sem);
            break;

        case 2:
            printf("\nEspiado Iniciado... \n\n");
            sem_wait(sem);
            spyProcesses();
            sem_post(sem);
            break;

        case 3:
            printf("\nSaliendo\n\n");
            //pidBlock[0] = -1; 
            return 0;

        break;
        
        default:
            printf("\nEl valor digitado es invalido\n");
            break;

        }
    }
}

