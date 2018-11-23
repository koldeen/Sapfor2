#!/usr/bin/env bash
LAUNCH_DIR=$(basename $(pwd))
TOP_DIR=examples
if [ "$LAUNCH_DIR" == "$TOP_DIR" ]; then
    echo "Building all examples"
    for d in ./*/ ; do (cd "$d" && ../rebuild.sh); done
    exit 0
fi
echo "---------------------------------"
echo "Building" $(basename $(pwd))
echo "Cleaning previous build"
source ../env.sh
source ../clean.sh
echo "Using parser: " ${PARSER_EXEC}
echo "Using ftransform: " ${FTRANSFORM_EXEC}
echo "Parsing..."
${PARSER_EXEC} -lgstd example.f90
echo "Transforming..."
${FTRANSFORM_EXEC} --silent --project dvm.proj
if [ ! -f trans.f90 ]; then
    (>&2 echo "ERROR: trans.f90 not found. Transformation failed.")
    echo "ERROR: trans.f90 not found. Transformation failed." > FAILURE
    exit 1
else
    echo "Validating..."
    source ../validate.sh
    diff -wBi expected.result.f90 trans.f90 > diff.txt
    echo "Output: trans.f90 with result FORTRAN code and simple.log with reports"
    if [ -s diff.txt ]; then
        (>&2 echo "ERROR: trans.f90 DIFFERS FROM EXPECTED program code")
        echo "ERROR: trans.f90 DIFFERS FROM EXPECTED program code" > FAILURE
        exit 1
    else
        echo "INFO: result code are equal"
        echo "INFO: result code are equal" > SUCCESS
        echo "SUCCESS"
    fi
fi

