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

    int *size;
    size = get_array_size(FILENAME, sizeof(int));
    size[0] = n;
    for (int i = 0; i < n; i++)
    {
        baseBlock[i].status = 0;
        baseBlock[i].PID = 0;
    }
    for (int i = 0; i < n; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, baseBlock[i].status);
    }
    shmdt((void *)baseBlock);
    shmdt((void *)size);
    int *borrar;
    borrar = get_array_size(FILENAME, sizeof(int));
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
