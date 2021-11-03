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
#include <time.h>

#define MAXPROGRAMCOUNT 5;

void extractProcess(int processPosition, int size, struct memoryBlock *blockList)
{
    for (int i = 0; i < size; i++)
    {
        blockList[processPosition + i].PID = -1;
        blockList[processPosition + i].status = 0;
    }
}

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
    // int lowerTime = 12; Better times for testing
    // int higherTime = 20;
    int lowerTime = 30;
    int higherTime = 60;
    return (rand() % (higherTime - lowerTime + 1)) + lowerTime;
}

void *popFromQueue(int pid, struct memoryBlock *queue)
{
    sem_t *sem;
    sem = sem_open(SEMAPHORE_NAME_QUEUE, 0, 0644, 0);
    sem_wait(sem);
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        if (queue[i].PID == pid)
        {
            queue[i].status = 0;
            queue[i].PID = -1;
            break;
        }
    }
    sem_post(sem);
}

void *changeQueueStatus(int pid, struct memoryBlock *queue, int status)
{
    sem_t *sem;
    sem = sem_open(SEMAPHORE_NAME_QUEUE, 0, 0644, 0);
    sem_wait(sem);
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        if (queue[i].PID == pid)
        {
            queue[i].status = status;
            break;
        }
    }
    sem_post(sem);
}
void *insertInReadyQueue(int pid, struct memoryBlock *queue)
{
    sem_t *sem;
    sem = sem_open(SEMAPHORE_NAME_QUEUE, 0, 0644, 0);
    sem_wait(sem);
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        if (queue[i].PID == -1)
        {
            queue[i].PID = pid;
            queue[i].status = 2;
            break;
        }
    }
    sem_post(sem);
}
void *printQueue(struct memoryBlock *queue)
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        printf("[id= %d queue = %d]", queue[i].PID, queue[i].status);
    }
    printf("\n");
}

void writeLog(struct threadStruct *process, int tipo, int pos)
{
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];
    char accion[70] = "gatito";
    // El formato.
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos =
        strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0)
    {
        FILE *fp;
        fp = fopen("log.txt", "a");
        fprintf(fp, "%s \n ", "─────────────────────────");
        fprintf(fp, "%s %d \n ", "Proceso #", process->id);
        fprintf(fp, "%s \n ", fechaHora);
        if (tipo == 0 || pos == -1)
        {
            fprintf(fp, "%s \n ", "Acción: asignando memoria.");
            fprintf(fp, "%s \n ", "No se pudo asignar memoria.");
        }
        else if (tipo == 1)
        {
            fprintf(fp, "%s \n ", "Acción: asignando memoria.");
            fprintf(fp, "%s \n ", "Se asigna los siguientes espacios en memoria:");

            int p_size = process->size;
            while (p_size > 0)
            {
                fprintf(fp, "%d \n ", pos++);
                p_size--;
            }
            fprintf(fp, "%s \n ", "Se ha asignado memoria correctamente.");
        }
        else if (tipo == 2)
        {
            fprintf(fp, "%s \n ", "Acción: desasignando memoria.");
            fprintf(fp, "%s \n ", "Se desasigna los siguientes espacios en memoria:");
            int p_size = process->size;
            while (p_size > 0)
            {
                fprintf(fp, "%d \n ", pos++);
                p_size--;
            }
            fprintf(fp, "%s \n ", "Se ha desasignado memoria correctamente.");
        }
        fclose(fp);
    }
}

void *searchSpace(void *process)
{
    sem_t *sem;

    struct threadStruct *processCast = (struct threadStruct *)process;
    sem = sem_open(SEMAPHORE_NAME_MEMORY, 0, 0644, 0);
    int len = get_array_size(FILENAME, 0)[0];
    int processPosition;
    insertInReadyQueue(processCast->id, processCast->queue);
    // Critical section
    sem_wait(sem);

    changeQueueStatus(processCast->id, processCast->queue, 3);

    // TODO: BITÁCORA LÍNEAS ASIGNADAS, LO PUEDE HACER LUEGO DEL EN LA SECCIÓN DE LA LÍNEA 142
    if (processCast->allocationAlgorithm == 1)
    {
        processPosition = first_fit(processCast->blockList, processCast->size, len, processCast->id);
        processCast->pos = processPosition;
        writeLog(processCast, 1, processPosition);
    }
    else if (processCast->allocationAlgorithm == 2)
    {
        processPosition = best_fit(processCast->blockList, processCast->size, len, processCast->id);
        processCast->pos = processPosition;
        writeLog(processCast, 1, processPosition);
    }
    else
    {
        processPosition = worst_fit(processCast->blockList, processCast->size, len, processCast->id);
        processCast->pos = processPosition;
        writeLog(processCast, 1, processPosition);
    }

    // Ends critical section

    sem_post(sem);
    changeQueueStatus(processCast->id, processCast->queue, 2);
    //Kills the process if couldn't find a space
    printQueue(processCast->queue);
    if (processPosition == -1)
    {
        // TODO: LOG DE NO ENTRÓ EN MEMORÍA
        //writeLog(processCast,0, 0);
        return;
    }
    // EN EL ELSE PUEDE MANDAR A BITÁCORA QUE LO ESCRIBIÓ EN LOS CAMPOS DESDE PROCESSPOSITION A PROCESSPOSITION + TAMAÑO DEL PROCESO
    sleep(processCast->runtime);
    popFromQueue(processCast->id, processCast->queue);
    sem_wait(sem);
    // TODO: LOG DE SE DESASIGNÓ DE MEMORIA
    extractProcess(processPosition, processCast->size, processCast->blockList);
    writeLog(processCast, 2, processCast->pos);
    processCast->pos = -1;
    sem_post(sem);
}

pthread_t *createProcess(int allocationAlgorithm, struct memoryBlock *blockList, int programId, struct memoryBlock *readyQueue)
{
    int size = getRandomSize();
    int runtime = getRandomExecutionTime();
    struct threadStruct *currentProcess = threadStruct();
    currentProcess->id = programId;
    currentProcess->allocationAlgorithm = allocationAlgorithm;
    currentProcess->runtime = runtime;
    currentProcess->size = size;
    currentProcess->blockList = blockList;
    currentProcess->queue = readyQueue;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, searchSpace, (void *)currentProcess);
    return thread_id;
}

int main(int argc, char const *argv[])
{

    int *pidBlock = get_processGenerator_id(FILENAME, sizeof(int));
    pidBlock[0] = getpid();
    // Select allocation algorithm
    srand(time(0));
    printf("Bienvenido al Programa Productor de Procesos, por favor seleccione con qué tipo de\
    allocación desea ejecutar el programa \n1 -> First Fit \n2 -> Best Fit\n3 -> Worst Fit\n>>> ");
    int option;
    scanf("%d", &option);
    printf("Opción %d", option);
    // Obtain the semaphore
    struct memoryBlock *blockList = attach_memory_block(FILENAME, 0);

    // Program creation cycle
    int programMaxCount = MAXPROGRAMCOUNT;
    int programCounter = 0;
    pthread_t lastThread;
    struct memoryBlock *queue = get_ready_queue(FILENAME);

    while (1)
    {
        lastThread = createProcess(option, blockList, programCounter, queue);
        programCounter++;
        sleep(getRandomWaitTime());
    }
    pthread_join(lastThread, NULL);

    return 0;
}
