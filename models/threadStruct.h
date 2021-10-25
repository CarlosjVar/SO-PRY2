#if !defined(THREADSTRUCT)
#define THREADSTRUCT
#include "./memoryBlock.h"
struct threadStruct
{
    int *id;
    int *indexInMemory;
    int *runtime;
    struct memoryBlock *blockList;
    struct memoryBlock *queue;
    int *allocationAlgorithm;
    int *size;
};
struct threadStruct *threadStruct();

void insert_process(int init, int p_size, struct memoryBlock *blockList, int arraySize, int pid);
int first_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);
int best_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);
int worst_fit(struct memoryBlock *blockList, int p_size, int arraySize, int pid);

#endif
