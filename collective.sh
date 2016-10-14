#!/bin/bash

mpicc -g src/collective.c -o bin/collective

echo ""
echo "2 processors, 32 messages, 5000 chars"
mpiexec -np 2 ./bin/collective 32 5000
echo ""
echo "4 processors, 32 messages, 5000 chars"
mpiexec -np 4 ./bin/collective 32 5000
echo ""
echo "8 processors, 32 messages, 5000 chars"
mpiexec -np 8 ./bin/collective 32 5000
echo ""
echo "16 processors, 32 messages, 5000 chars"
mpiexec -np 16 ./bin/collective 32 5000

echo ""
echo "2 processors, 32000 messages, 5000 chars"
mpiexec -np 2 ./bin/collective 32000 5000
echo ""
echo "4 processors, 32000 messages, 5000 chars"
mpiexec -np 4 ./bin/collective 32000 5000
echo ""
echo "8 processors, 32000 messages, 5000 chars"
mpiexec -np 8 ./bin/collective 32000 5000
echo ""
echo "16 processors, 32000 messages, 5000 chars"
mpiexec -np 16 ./bin/collective 32000 5000
