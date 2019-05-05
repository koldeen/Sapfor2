#!/usr/bin/env bash
rm ftransform
rm -rf build
mkdir build
cd build
cmake ..
cmake --build . && COMPILED=OK
if [[ -n $COMPILED ]]; then
(cd .. && source prepare_tests.sh)
ctest -V
else
echo "BUILD FAILED. Tests not launched."
fi
cd ..
cp ./build/ftransform ./ftransform
