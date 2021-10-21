#include "../sharedMem.h"
#include "../memory.h"
#include "../memoryBlock.h"
#include <stdio.h>
#define IPC_RESULT_ERROR (-1)
void startMemory()
{
    printf("Ingrese la cantidad de espacios de memoria que desea reservar \n");
    int n;
    scanf("%d", &n);

    int bloque = get_shared_memory(FILENAME, BLOCK_SIZE);
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
