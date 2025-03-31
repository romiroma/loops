#!/bin/bash

# This is a placeholder for your build script.
# Add your build commands below.

echo "Starting the build process..."
mkdir -p build
mkdir -p lib
# Example: Compile a program
INCLUDE_DIR="include"

# Assemble test.asm into an object file
nasm -f elf64 $1 -o build/test.o src/$2/*.asm
gcc -I"$INCLUDE_DIR" -mavx -mavx2 $1 -c -o  build/test_c_simd.o src/$2/test_c_simd.c
# Compile tests.c as a library
gcc -I"$INCLUDE_DIR" -mavx -mavx2 $1 -c -o  build/tests.o src/tests.c
# Pack test.o into a static library
ar rcsD lib/libtest.a build/test.o
# Pack tests.o into a static library
ar rcsD lib/libtests.a build/tests.o
# Pack test_c_simd.o into a static library
ar rcsD lib/libtest_c_simd.a build/test_c_simd.o

# Compile main.c and link it with the library
gcc -I"$INCLUDE_DIR" -mavx -mavx2 $1 -o main src/main.c -L./lib -ltests -ltest -ltest_c_simd
