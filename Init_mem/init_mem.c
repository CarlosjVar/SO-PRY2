#include "../sharedMem.h"
#include "../models/memoryBlock.h"
#include <string.h>
#include <pthread.h>
#include <stdio.h>  /* printf()                 */
#include <stdlib.h> /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h> /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>   /* shmat(), IPC_RMID        */
#include <errno.h>     /* errno, ECHILD            */
#include <semaphore.h> /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>     /* O_CREAT, O_EXEC          */
#define IPC_RESULT_ERROR (-1)
void startMemory()
{
    struct memoryBlock *baseBlock;

    // Initialize semaphore
    sem_t *sem;
    int *count = malloc(sizeof(int));
    count = 1;
    sem = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0644, count);
    if (sem == SEM_FAILED)
    {
        perror("error");
    }
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
        baseBlock[i].PID = -1;
    }

    // baseBlock[4].status = 1;
    for (int i = 0; i < n; i++)
    {
        printf("El  bloque tiene PID %d  status %d  \n", i, baseBlock[i].status);
    }
    shmdt((void *)baseBlock);
    shmdt((void *)size);
    sem_close(sem);
    int *borrar;
    borrar = get_array_size(FILENAME, sizeof(int));
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
