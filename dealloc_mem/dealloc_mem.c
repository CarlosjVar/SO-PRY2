#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sharedMem.h"

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
    return 0;
}
