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
    baseBlock[0].PID = 77;
    baseBlock[0].status = 1;
    // baseBlock[1].PID = 0;
    // baseBlock[1].status = 0;
    // baseBlock[2].PID = 0;
    // baseBlock[2].status = 0;
    baseBlock[3].PID = 24;
    baseBlock[3].status = 1;
    baseBlock[4].PID = 33;
    baseBlock[4].status = 1;
    // baseBlock[5].PID = 0;
    // baseBlock[5].status = 0;
    
    // baseBlock[6].PID = 0;
    // baseBlock[6].status = 0;
    // baseBlock[7].PID = 0;
    // baseBlock[7].status = 0;
    // baseBlock[8].PID = 0;
    // baseBlock[8].status = 0;
    baseBlock[9].PID = 99;
    baseBlock[9].status = 1;

    int *size;
    size = get_array_size(FILENAME, sizeof(int));
    size[0] = n;
    shmdt((void *)baseBlock);
    shmdt((void *)size);
    int *borrar;
    borrar = get_array_size(FILENAME, sizeof(int));
    printf("llega aqui pene %d", borrar[0]);
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
