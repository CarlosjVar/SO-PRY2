#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem.h"

int main(int argc, char *argv[]) {

     if(argc != 1){
        printf("usage - %s // no args", argv[0]);
        return -1;
    }

    if(destroy_memory_block(FILENAME)){
        printf("Bloque destruido: %s\n", FILENAME);        
    }else{        
        printf("Imposible destruir el bloque: %s\n", FILENAME); 
    }

    printf("Fin de la destruccion");

    return 0;

}