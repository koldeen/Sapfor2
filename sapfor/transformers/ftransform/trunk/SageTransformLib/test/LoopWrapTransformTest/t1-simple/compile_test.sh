#!/usr/bin/env bash
gfortran valid.f90 -o valid.exe
gfortran expected.fin.f90 -o expected.exe
gfortran result.fin.f90 -o result.exe
./valid.exe > valid.txt
./expected.exe > expected.txt
./result.exe > result.txt
diff valid.txt expected.txt > diff.txt
if [ -s diff.txt ]; then
    (>&2 echo "BAD_TEST: Expected program is not same as initial")
    echo "BAD_TEST: Expected program is not same as initial" > BAD_TEST
    exit 1
else
    diff valid.txt result.txt > diff.txt
    if [ -s diff.txt ]; then
        (>&2 echo "FAILURE: Code does not pass the test")
        echo "FAILURE: Code does not pass the test" > FAILURE
        exit 1
    else
        echo "SUCCESS: Valid test results"
        echo "SUCCESS: Valid test results" > SUCCESS
    fi
fi
