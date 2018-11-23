#!/usr/bin/env bash
printf "Removing everything except original example Fortran and scripts..."
rm *.proj *.dep *.exe *.txt
rm -rf sapfor_out
rm -f FAILURE SUCCESS BAD_TEST
printf " Done\n"