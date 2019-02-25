#!/usr/bin/env bash
function compile {
    "$@"
    local status=$?
    if [ $status -ne 0 ]; then
        (>&2 echo "ERROR: with $1")
        exit $status
    fi
}

compile $(gfortran -o example.exe example.f90)
compile $(gfortran -o expected.result.exe expected.result.f90)
compile $(gfortran -o trans.exe trans.f90)
./example.exe >example.txt
./expected.result.exe >expected.result.txt
./trans.exe >trans.txt
diff example.txt expected.result.txt > diff.txt
if [ -s diff.txt ]; then
    (>&2 echo "ERROR: Test is invalid, expected result output differs from original program output")
    echo "ERROR: Test is invalid, expected result output differs from original program output" > BAD_TEST
fi
diff expected.result.txt trans.txt > diff.txt
if [ -s diff.txt ]; then
    (>&2 echo "ERROR: Transformation broke the program, outputs are different")
    echo "ERROR: Transformation broke the program, outputs are different" > FAILURE
else
    echo "INFO: Transformed program gave same result"
fi
