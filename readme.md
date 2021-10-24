# Comandos para compilar los diferentes programas
Todos estos comandos son ejecutados desde el root (/SO-PRY2)
## Programa inicializador
```
gcc ./init_mem/init_mem.c  sharedMem.c -o init
```

## Programa finalizador

```
gcc ./dealloc_mem/dealloc_mem.c sharedMem.c -o output/dealloc
```

