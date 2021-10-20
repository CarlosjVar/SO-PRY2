#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem.h"

int main(int argc, char *argv[]) {

    if(argc != 1){
        printf("usage - %s // no args", argv[0]);
        return -1;
    }


    char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

    if(bloque == NULL){
        printf("Imposible conseguir el bloque\n");
        return -1;
    }

    printf("Leyendo: \"%s\"\n", bloque);

    detach_memory_block(bloque);

    printf("Fin de la lectura\n\n");

    return 0;

}
