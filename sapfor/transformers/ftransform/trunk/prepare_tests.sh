#!/usr/bin/env bash
(cd ../SageTransformLib/test/LoopTransformTightenTest; ../../../parser/parser -lgstd valid.f90; rm dvm.proj;\
 echo "../../SageTransformLib/test/LoopTransformTightenTest/valid.dep" > valid.proj)
(cd ../SageUtils/test/LineReordererTest; ../../../parser/parser -lgstd valid.f90; rm dvm.proj;\
 echo "../../SageUtils/test/LineReordererTest/valid.dep" > valid.proj)
