#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sharedMem.h"
#include <semaphore.h> /* sem_open(), sem_destroy(), sem_wait().. */
#include <sys/types.h> /* key_t, sem_t, pid_t      */

int destroyBlock()
{

    if (destroy_memory_block(FILENAME))
    {
        printf("Bloque destruido: %s\n", FILENAME);
    }
    else
    {
        printf("Imposible destruir el bloque: %s\n", FILENAME);
    }

    printf("Fin de la destruccion");

    return 0;
}
int main(int argc, char const *argv[])
{
    destroyBlock(FILENAME);
    sem_unlink(SEMAPHORE_NAME);
    return 0;
}
