#!/bin/bash

# Building malloc.so
gcc -shared -o libmalloc.so malloc.c -D_SMALLOC_EXPORTS
if [ $? -ne 0 ]; then
    echo "Error compiling libmalloc.so"
    exit 1
fi

# Building arena.so with linking to malloc.so
gcc -shared -o libarena.so arena.c -D_ARENA_EXPORTS -L. -lmalloc
if [ $? -ne 0 ]; then
    echo "Error compiling libarena.so"
    exit 1
fi

echo "Libraries compiled successfully!"
