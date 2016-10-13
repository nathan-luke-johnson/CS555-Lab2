#!/bin/bash

mpicc -g src/performance.c -o bin/performance

mpiexec -np 2 ./bin/performance 2 100000
mpiexec -np 4 ./bin/performance 4 100000
mpiexec -np 8 ./bin/performance 8 100000
mpiexec -np 16 ./bin/performance 16 100000
