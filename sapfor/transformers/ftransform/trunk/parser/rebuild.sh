#!/usr/bin/env bash
rm parser
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cp ./build/parser ./parser
