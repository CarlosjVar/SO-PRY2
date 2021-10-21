#include "../sharedMem.h"
#include "../models/memory.h"
#include "../models/memoryBlock.h"
#include <stdio.h>
#define IPC_RESULT_ERROR (-1)
void startMemory()
{

    printf("Ingrese la cantidad de espacios de memoria que desea reservar \n");
    int n;
    scanf("%d", &n);
    int requiredBlockSize = n * sizeof(struct memoryBlock) + sizeof(struct memory);
    int bloque = create_shared_memory(FILENAME, requiredBlockSize);
    if (bloque == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return;
    }
    printf("%d", bloque);
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
