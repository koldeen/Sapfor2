#!/usr/bin/env bash
../../clean.sh
source ../../env.sh
../../../_bin/$PARSER_EXEC program.f90
gfortran program.f90 -o program.exe
./program.exe > program.out.txt
mkdir sapfor_out
../../../_bin/$SAPFOR_EXEC -pass 3 -F sapfor_out -print
gfortran sapfor_out/program.f90 -o sapfor_out/program.exe
sapfor_out/program.exe > sapfor_out/program.out.txt
diff program.out.txt sapfor_out/program.out.txt > diff.txt
if [ -s diff.txt ]; then
    (>&2 echo "ERROR: Sapfor result program behavior differs from original program")
    echo "ERROR: Sapfor result program behavior differs from original program" > FAILURE
else
    echo "Sapfor result program behavior is same as original program"
    echo "Checking sources"
    diff -b program.expected.f90 sapfor_out/program.f90 > diff.txt
    if [ -s diff.txt ]; then
        (>&2 echo "ERROR: Sapfor result program code differs from original program")
        echo "ERROR: Sapfor result program code differs from original program" > FAILURE
    else
        echo "SUCCESS: Sapfor result as expected (sources and compiled)"
        echo "SUCCESS: Sapfor result as expected (sources and compiled)" > SUCCESS
    fi
fi
