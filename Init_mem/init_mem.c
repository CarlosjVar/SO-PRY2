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
    sem_t *semM;
    sem_t *semQ;
    int *count = malloc(sizeof(int));
    count = 1;
    semM = sem_open(SEMAPHORE_NAME_MEMORY, O_CREAT | O_EXCL, 0644, count);
    if (semM == SEM_FAILED)
    {
        perror("error");
    }
    semQ = sem_open(SEMAPHORE_NAME_QUEUE, O_CREAT | O_EXCL, 0644, count);

    printf("Ingrese la cantidad de espacios de memoria que desea reservar \n");
    int n;
    scanf("%d", &n);
    int requiredBlockSize = n * sizeof(*baseBlock);

    int shmid;

    baseBlock = create_memory_block(FILENAME, requiredBlockSize);

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
    struct memoryBlock *queue = get_ready_queue(FILENAME);
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        queue[i].status = 0;
        queue[i].PID = -1;
    }
    shmdt((void *)baseBlock);
    shmdt((void *)size);
    sem_close(semM);
    sem_close(semQ);
    int *borrar;
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente\n");
    return 0;
}
