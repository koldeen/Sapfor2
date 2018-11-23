#!/usr/bin/env bash
printf "Removing everything except original example Fortran and scripts..."
rm *.proj *.dep *.log *.backup trans.f90 diff.txt 2> /dev/null
rm example.exe expected.result.exe trans.exe example.txt expected.result.txt trans.txt 2> /dev/null
rm FAILURE SUCCESS BAD_TEST 2> /dev/null
printf " Done\n"