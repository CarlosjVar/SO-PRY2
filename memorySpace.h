#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharedMem"
#include "blockreading.c"
#include "blockwriting.c"
#include "blockdestruction.c"

struct memorySpace{

    int memorySize;
    int memoryPosition;


};

