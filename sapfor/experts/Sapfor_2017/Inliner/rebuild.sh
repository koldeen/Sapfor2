#!/usr/bin/env bash
rm ../_bin/Inliner_cmake.exe
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cp ./build/Inliner ../_bin/Inliner_cmake.exe
