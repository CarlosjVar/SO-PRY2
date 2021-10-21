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
    int bloque = create_shared_memory(FILENAME, 50 * sizeof(int));
    if (bloque == IPC_RESULT_ERROR)
    {
        printf("No se pudo encontrar la llave para el bloque\n");
        return;
    }
    // Initialize starting array
    struct memory *memSpace;
    int *array;
    array = (int *)shmat(bloque, 0, 0);
    for (int i; i < n; i++)
    {
        array[i] = i;
    }
    for (int i; i < n; i++)
    {
        printf("%d", array[i]);
    }

    printf("Antes assign");
    printf("Luego assign");
    // if (memSpace == (struct memory *)IPC_RESULT_ERROR)
    // {
    //     printf("No se pudo reservar el espacio\n");
    // }
    // detach_memory_block(memSpace);
}

int main(int argc, char const *argv[])
{
    startMemory();
    printf("Bloque creado correctamente");
    return 0;
}
