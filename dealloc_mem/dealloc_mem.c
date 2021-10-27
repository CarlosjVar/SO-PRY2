#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../sharedMem.h"
#include <semaphore.h> /* sem_open(), sem_destroy(), sem_wait().. */
#include <sys/types.h> /* key_t, sem_t, pid_t      */
#include <signal.h>

#define SIGTERM 15

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

    return 0;
}

void stopProcesses(){
 
    int *generatorId = get_processGenerator_id(FILENAME, sizeof(int));
    int *spyId = get_spy_id(FILENAME, sizeof(int));

    if(generatorId[0] != 0){
        kill(generatorId[0], SIGTERM);
    }

    if(spyId[0] != 0){
        kill(spyId[0], SIGTERM);
    }
    
}

int main(int argc, char const *argv[])
{

    stopProcesses();
    destroyBlock(FILENAME);
    sem_unlink(SEMAPHORE_NAME_MEMORY);
    sem_unlink(SEMAPHORE_NAME_QUEUE);
    return 0;
}
