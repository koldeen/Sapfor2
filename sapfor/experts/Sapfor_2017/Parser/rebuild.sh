#!/usr/bin/env bash
rm ../_bin/Parser_cmake.exe
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cp ./build/Parser ../_bin/Parser_cmake.exe
