#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoryBlock.h"

struct memory
{

    struct memoryBlock *memoryArray;
    int memorySize;
};
#endif