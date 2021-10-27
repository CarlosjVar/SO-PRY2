# Comandos para compilar los diferentes programas

Todos estos comandos son ejecutados desde el root (/SO-PRY2)

## Programa inicializador

```
gcc ./Init_mem/init_mem.c  sharedMem.c  ./models/memoryBlock.c -pthread -o init

```

## Programa productor de procesos

```
gcc ./program_factory/program_factory.c sharedMem.c ./models/memoryBlock.c ./models/threadStruct.c -pthread -o producer -w
```

## Programa espia

```
gcc -pthread spy_mem/spy_mem.c sharedMem.c -o spy_memory
```

## Programa finalizador

```
gcc ./dealloc_mem/dealloc_mem.c sharedMem.c -pthread  -o dealloc
```
