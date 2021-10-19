#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
static int * getMemBlock(char *filename, int size);
char *attach_memblock(char *filename, int size);
#endif