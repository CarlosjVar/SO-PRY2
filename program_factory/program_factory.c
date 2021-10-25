#include "program_factory.h"
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
#include "../sharedMem.h"
#include "../models/memoryBlock.h"
#include "../models/threadStruct.h"
#include <fcntl.h> /* O_CREAT, O_EXEC          */

#define MAXPROGRAMCOUNT 5;

int getRandomSize()
{
    int minSpace = 1;
    int maxSpace = 10;
    return (rand() % (maxSpace - minSpace + 1)) + minSpace;
}

int getRandomExecutionTime()
{
    int lowerTime = 20;
    int higherTime = 60;
    return (rand() % (higherTime - lowerTime + 1)) + lowerTime;
}
int getRandomWaitTime()
{
    int lowerTime = 30;
    int higherTime = 60;
    return (rand() % (higherTime - lowerTime + 1)) + lowerTime;
}
void *searchSpace(void *process)
{

    sem_t *sem;
    struct threadStruct *processCast = (struct threadStruct *)process;
    sem = sem_open("pSem", 0, 0644, 0);
    sem_wait(sem);
    printf("Soy un gordo de  %d espacios \n", processCast->size);
    int len = get_array_size(FILENAME, 0)[0];
    switch (*processCast->allocationAlgorithm)
    {
    case 1:
        first_fit(processCast->blockList, processCast->size, len, processCast->id);
        break;
    case 2:
        best_fit(processCast->blockList, processCast->size, len, processCast->id);
        break;
    case 3:
        worst_fit(processCast->blockList, processCast->size, len, processCast->id);
        break;
    }
    sem_post(sem);
    // Missing the part where the program exits memory
}

pthread_t *createProcess(int *allocationAlgorithm, struct memoryBlock *blockList, int programId)
{
    int size = getRandomSize();
    int runtime = getRandomExecutionTime();
    //printf("%d", runtime);
    struct threadStruct *currentProcess = threadStruct();
    currentProcess->id = programId;
    //printf("Hola");
    currentProcess->allocationAlgorithm = allocationAlgorithm;
    currentProcess->runtime = runtime;
    currentProcess->size = size;
    currentProcess->blockList = blockList;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, searchSpace, (void *)currentProcess);
    return thread_id;
}

int main(int argc, char const *argv[])
{
    // Select allocation algorithm
    srand(time(0));
    printf("Bienvenido al Programa Productor de Procesos, por favor seleccione con qué tipo de\
    allocación desea ejecutar el programa \n1 -> First Fit \n2 -> Best Fit\n3 -> Worst Fit\n>>> ");
    int *option;
    scanf("%d", &option);
    printf("Opción %d", option);
    // Obtain the semaphore
    sem_t *sem;
    sem = sem_open("pSem", 0, 0644, 0);
    struct memoryBlock *blockList = attach_memory_block(FILENAME, 0);

    // Program creation cycle
    int programMaxCount = MAXPROGRAMCOUNT;
    int programCounter = 0;
    pthread_t lastThread;
    for (int i = 0; i < programMaxCount; i++)
    {
        lastThread = createProcess(option, blockList, programCounter);
        programCounter++;
        //sleep(getRandomWaitTime());
    }
    pthread_join(lastThread, NULL);
    // pthread_t a[10];

    // for (int i = 0; i < 10; i++)
    // {
    //     pthread_t thread_id;
    //     pthread_create(&thread_id, NULL, myfunc, i);

    //     a[i] = thread_id;
    // }
    // for (int i = 0; i < 10; i++)
    // {
    //     pthread_join(a[i], NULL);
    // }
    sem_close(sem);
    return 0;
}
