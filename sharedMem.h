#ifndef SHARED_MEMORY_H

#define SHARED_MEMORY_H
#include <stdbool.h>
#include "models/memoryBlock.h"
int create_shared_memory(char *filename, int size);
int get_shared_memory(char *filename, int size);
// Creates shared memory if not exists
struct memoryBlock *create_memory_block(char *filename, int size);
// Gives error if shared memory doesn't exists
struct memoryBlock *attach_memory_block(char *filename, int size);
bool detach_memory_block(char *block);
bool destroy_memory_block(char *filename);
int create_array_size(char *filename, int size);
int *get_array_size(char *filename, int size);

#define BLOCK_SIZE 4096
#define FILENAME "memblock.c"
#define SEMAPHORE_NAME "pSem"

#endif