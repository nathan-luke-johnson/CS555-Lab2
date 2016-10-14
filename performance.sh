#!/bin/bash

mpicc -g src/performance.c -o bin/performance

echo ""
echo "20 messages, 80 chars"
mpiexec -np 2 ./bin/performance 20 80
echo ""
echo "40 messages, 40 chars"
mpiexec -np 2 ./bin/performance 40 40
echo ""
echo "80 messages, 20 chars"
mpiexec -np 2 ./bin/performance 80 20
