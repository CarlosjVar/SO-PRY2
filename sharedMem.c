#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sharedMem.h"

#define BLOCK_SIZE 4096
#define FILENAME "memblock.c"
#define IPC_RESULT_ERROR (-1)


static int get_shared_memory(char *filename, int size, int space){

    key_t key;

    key = ftok(filename, space);
    if(key == IPC_RESULT_ERROR){
        printf("La llave no se pudo conseguir con exito\n");
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);

}

char * attach_memory_block(char *filename, int size, int space){

    int memblock = get_shared_memory(filename, size, space);
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

//  int main(int argc, char *argv[]) {


//     // if(argc != 2){
//     //     printf("usage - %s [stuff to write]", argv[0]);
//     // }


//     // char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

//     // if(bloque == NULL){
//     //     printf("Imposible conseguir el bloque\n");
//     //     return -1;
//     // }
//     // printf("Escribiendo: \"%s\"\n", argv[1]);
//     // strncpy(bloque,argv[1],BLOCK_SIZE);

//     // detach_memory_block(bloque);

//     // printf("Fin de la escritura\n\n");

//     // return 0;

// ///////////////////////////////////////////////////////

//     if(argc != 1){
//         printf("usage - %s // no args", argv[0]);
//         return -1;
//     }


//     char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

//     if(bloque == NULL){
//         printf("Imposible conseguir el bloque\n");
//         return -1;
//     }

//     printf("Leyendo: \"%s\"\n", bloque);

//     detach_memory_block(bloque);

//     printf("Fin de la lectura\n\n");

//     return 0;

// }