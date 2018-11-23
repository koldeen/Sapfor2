#!/usr/bin/env bash
rm ./_bin/Sapfor_2017_cmake.exe
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cp ./build/Sapfor_2017 ./_bin/Sapfor_2017_cmake.exe
