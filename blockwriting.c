#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem.h"

int writeInBlock() {

    char ch;

    printf("\n\n Introduzca un caracter a guardar: ");
    scanf("%c", &ch);

    char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

    if(bloque == NULL){
        printf("Imposible conseguir el bloque\n");
        return -1;
    }
    printf("Escribiendo: \"%s\"\n", ch);
    strncpy(bloque, &ch, BLOCK_SIZE);

    detach_memory_block(bloque);

    printf("Fin de la escritura\n\n");

    return 0;
}
