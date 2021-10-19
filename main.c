#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#define BLOCK_SIZE 4096
#define FILENAME "memblock.c"
#define IPC_RESULT_ERROR (-1)


static int get_shared_memory(char *filename, int size){

    key_t key;

    key = ftok(filename,0);
    if(key == IPC_RESULT_ERROR){
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);

}

char * attach_memory_block(char *filename, int size){

    int memblock = get_shared_memory(filename, size);
    char *result;

    if(memblock == IPC_RESULT_ERROR){
        printf("No se pudo encontrar la llave para el bloque\n");
        return NULL;
    }

    result = shmat(memblock, NULL, 0);

    if(result == (char *) IPC_RESULT_ERROR){
        printf("No se pudo reservar el espacio\n");
        return NULL;
    }

    return result;

}

bool detach_memory_block(char *block){
    return(shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *filename){
    
    int memblock = get_shared_memory(filename,0);

    if (memblock == IPC_RESULT_ERROR){
        printf("Imposible destruir memoria, archivo no encontrado\n");
        return NULL;
    }
    return(shmctl(memblock, IPC_RMID, NULL)!= IPC_RESULT_ERROR);
    
}

int main(int argc, char *argv[]) {

    char *var = attach_memory_block(FILENAME, BLOCK_SIZE);

    if(var == NULL){
        printf("Imposible conseguir el bloque\n");
    }else{
        printf("pene");
    }


    printf("\n\n");
}