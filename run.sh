#!/usr/bin/env bash

set -e

if [ -z "$1" ] ; then
    echo "Usage: ./run.sh <number>"
    exit 1
fi

src=$1/main.c
out=build/$1
exec=$out/main

mkdir -p $out

clang -Wall -Wextra -O0 -o $exec $src

chmod +x $exec

./$exec $1
