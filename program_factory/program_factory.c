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
#include <fcntl.h> /* O_CREAT, O_EXEC          */
void *myfunc(void *id)
{
    sem_t *sem;

    sem = sem_open("pSem", 0, 0644, 0);
    sem_wait(sem);
    printf("Soy el thread %d\n", id);
    sem_post(sem);
}

int main(int argc, char const *argv[])
{
    printf("Bienvenido al Programa Productor de Procesos, por favor seleccione con qué tipo de\
    allocación desea ejecutar el programa \n1 -> First Fit \n2 -> Best Fit\n3 -> Worst Fit\n>>> ");
    int *option;
    scanf("%d", &option);
    printf("Opción %d", option);
    sem_t *sem;
    sem = sem_open("pSem", 0, 0644, 0);
    pthread_t a[10];
    for (int i = 0; i < 10; i++)
    {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, myfunc, i);

        a[i] = thread_id;
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(a[i], NULL);
    }
    sem_close(sem);
    return 0;
}
