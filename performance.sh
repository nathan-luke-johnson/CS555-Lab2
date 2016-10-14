#!/bin/bash

mpicc -g src/performance.c -o bin/performance

echo ""
echo "1 message, 0 chars"
mpiexec -np 2 ./bin/performance 1 0
echo ""
echo "1 messages, 5120000 chars"
mpiexec -np 2 ./bin/performance 1 5120000
echo ""
echo "10000 messages, 160000 chars"
mpiexec -np 2 ./bin/performance 10000 160000
echo ""
echo "20000 messages, 80000 chars"
mpiexec -np 2 ./bin/performance 20000 80000
echo ""
echo "40000 messages, 40000 chars"
mpiexec -np 2 ./bin/performance 40000 40000
echo ""
echo "80000 messages, 20000 chars"
mpiexec -np 2 ./bin/performance 80000 20000
echo ""
echo "160000 messages, 10000 chars"
mpiexec -np 2 ./bin/performance 160000 10000
echo ""
echo "320000 messages, 5000 chars"
mpiexec -np 2 ./bin/performance 320000 5000
