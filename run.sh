#!/bin/bash
# Usage: ./run.sh filename_without_extension
# Example: ./run.sh hashmap
FILE=${1:-solution}
gcc -Wall -Wextra -o $FILE $FILE.c && ./$FILE
