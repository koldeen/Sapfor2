#!/usr/bin/env bash
(cd ../SageTransformLib/test/LoopTransformTightenTest; ../../../parser/parser -lgstd valid.f90; rm dvm.proj;)
(cd ../SageUtils/test/LineReordererTest; ../../../parser/parser -lgstd valid.f90; rm dvm.proj;)
(cd ../SageUtils/test/SageTransformUtilsTest; ../../../parser/parser -lgstd swapWithLexPrev.f90; rm dvm.proj;)
