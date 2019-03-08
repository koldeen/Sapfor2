#!/usr/bin/env bash
(cd ./SageTransformLib/test/LoopTransformTightenTest/t1-simple && pwd && ../../../../parser/parser valid.f90 && rm dvm.proj && echo OK)
(cd ./SageTransformLib/test/LoopTransformTightenTest/t2-jac && pwd && ../../../../parser/parser valid.f90 && rm dvm.proj && echo OK)
(cd ./SageTransformLib/test/LoopWrapTransformTest/t1-simple && pwd && ../../../../parser/parser valid.f90 && rm dvm.proj && echo OK)
(cd ./SageUtils/test/LineReordererTest && pwd && ../../../parser/parser valid.f90 && rm dvm.proj && echo OK)
(cd ./SageUtils/test/SageTransformUtilsTest && pwd && ../../../parser/parser swapWithLexPrev.f90 && rm dvm.proj && echo OK)
