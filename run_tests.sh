#!/bin/bash

ARCH=$(uname -m)
./build.sh $1 $ARCH &&
./main
if [ $? -ne 0 ]; then
    echo "Tests failed!"
    exit 1
fi

echo "All tests passed."
./clean.sh