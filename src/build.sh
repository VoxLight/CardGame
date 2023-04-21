#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 <output file name>"
  exit 1
fi

# Find all .c files in the current directory
C_FILES=$(find . -maxdepth 1 -name '*.c' -printf '%f ')
C_LIBS=$(find ./libs -name '*.c' -printf './libs/%f ')

# Build the files with gcc and include the current directory
gcc -g $C_FILES $C_LIBS -I. -I./libs -o $1