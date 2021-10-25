
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
int main(int argc, char const *argv[])
{
    sem_t *sem;

    sem = sem_open("pSem", 0, 0644, 0);
    sem_wait(sem);
    printf("llegué papillo");
    sem_post(sem);
    return 0;
}
