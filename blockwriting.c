#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem.h"

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("usage - %s [stuff to write]", argv[0]);
    }


    char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

    if(bloque == NULL){
        printf("Imposible conseguir el bloque\n");
        return -1;
    }
    printf("Escribiendo: \"%s\"\n", argv[1]);
    strncpy(bloque,argv[1],BLOCK_SIZE);

    detach_memory_block(bloque);

    printf("Fin de la escritura\n\n");

    return 0;
}
