#!/bin/bash

mpicc -g src/performance.c -o bin/performance

echo ""
echo "2 processors"
mpiexec -np 2 ./bin/performance 2 100
echo ""
echo "4 processors"
mpiexec -np 4 ./bin/performance 4 100
echo ""
echo "8 processors"
mpiexec -np 8 ./bin/performance 8 100
echo ""
echo "16 processors"
mpiexec -np 16 ./bin/performance 16 100
