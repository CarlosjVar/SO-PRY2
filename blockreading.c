#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem.h"

int readBlock()
{

    char *bloque = attach_memory_block(FILENAME, BLOCK_SIZE);

    if (bloque == NULL)
    {
        printf("Imposible conseguir el bloque\n");
        return -1;
    }

    printf("Leyendo: \"%s\"\n", bloque);

    detach_memory_block(bloque);

    printf("Fin de la lectura\n\n");

    return 0;
}

int main(int argc, char const *argv[])
{
    readBlock();
    return 0;
}
