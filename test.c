#include "sharedMem.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
    int shmid;
    int *array;
    int count = 5;
    int i = 0;
    int SizeMem;
    key_t key = 12345;

    SizeMem = sizeof(*array) * count;

    shmid = shmget(key, count * sizeof(int), IPC_CREAT);

    array = (int *)shmat(shmid, 0, 0);

    //array = malloc(sizeof(int) * count);

    for (i = 0; i < 5; i++)
    {
        array[i] = i;
    }

    for (i = 0; i < count; i++)
    {
        printf("\n%d---\n", array[i]);
    }

    printf("\nWritting to memory succesful--\n");

    shmdt((void *)array);

    return 0;
}