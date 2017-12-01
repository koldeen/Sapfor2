#!/usr/bin/env bash
rm ftransform
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
(cd ../SageTransformLib/test/LoopTransformTightenTest;\
 ../../../parser/parser -lgstd valid.f90;\
 rm dvm.proj;\
 echo "../../SageTransformLib/test/LoopTransformTightenTest/valid.dep" > valid.proj)
ctest
cd ..
cp ./build/ftransform ./ftransform
