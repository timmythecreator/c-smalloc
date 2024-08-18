#!/bin/bash

# Building test.exe using malloc.so and arena.so
gcc -o test test.c -L. -larena -lmalloc
if [ $? -ne 0 ]; then
    echo "Error compiling test"
    exit 1
fi

echo "Test program compiled successfully!"