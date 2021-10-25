#if !defined(THREADSTRUCT)
#define THREADSTRUCT
#include "./memoryBlock.h"
struct threadStruct
{
    int *id;
    int *indexInMemory;
    int *runtime;
    struct memoryBlock *blockList;
    int *allocationAlgorithm;
    int *size;
};
struct threadStruct *threadStruct();

void insert_process(int init, int p_size, struct memoryBlock *blockList, int arraySize, int pid);
void first_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);
void best_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);
void worst_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);

#endif
